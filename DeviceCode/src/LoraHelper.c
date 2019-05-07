#include "LoraHelper.h"
#include <DataRepository.h>
#include <ihal.h>
#include <lora_driver.h>
#include <util/delay.h>


#define LORA_IO_TASK_PRIORITY (tskIDLE_PRIORITY+2)

#define LORA_appEUI "40f0e6960ec746d8"
#define LORA_appKEY "234cc8845c2087ff6a56deb1f9c1d5b4"

#define LORA_SECONDS_TO_WAIT 60

#define CO2_LOW_PAYLOAD_INDEX 0
#define CO2_HIGH_PAYLOAD_INDEX 1
#define TEMP_PAYLOAD_INDEX 2
#define HUMIDITY_PAYLOAD_INDEX 3
#define LIGHT_PAYLOAD_INDEX 4
#define MOVEMENT_PAYLOAD_INDEX 5
#define LORA_INIT_TASK_PRIORITY 7

static preferences_t* privatePreferences;
static SemaphoreHandle_t* privateSemaphore;
static sensor_data_t* privateSensorData;
static TaskHandle_t ioTaskHandle=NULL;
static TimerHandle_t loraTimer;


// 5 minute delay in ticks + 5s

void lora_setup();

void lora_timer_callback(TimerHandle_t pxTimer);

void initialize_lora_helper(sensor_data_t *sensorData, SemaphoreHandle_t *semaphoreHandle, preferences_t *preferences){
	privatePreferences=preferences;
	privateSemaphore=semaphoreHandle;
	privateSensorData=sensorData;

	xTaskCreate(handle_message, "MESSAGE_HANDLE", configMINIMAL_STACK_SIZE, NULL, LORA_IO_TASK_PRIORITY, &ioTaskHandle);

	hal_create(LORA_INIT_TASK_PRIORITY+1);
	lora_driver_create(ser_USART1);

	vTaskSuspend(ioTaskHandle);
	loraTimer= xTimerCreate("SENSOR_TIMER", ONE_SECOND_SENSOR_TIMER*LORA_SECONDS_TO_WAIT, pdFALSE, (void *) 0, lora_timer_callback);
	xTimerStart(loraTimer,0);
}

void handle_message(){
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wmissing-noreturn"
	TickType_t xLastWakeTimeLoraSendOff=xTaskGetTickCount();
	lora_setup();
	while(1){
		//FIXME IMPLEMENT ME
		xSemaphoreTake(*privateSemaphore,ONE_SECOND_SENSOR_TIMER);
		lora_payload_t loraPayload;
		loraPayload.len=7;
		// Separating
		unsigned char lsb = (unsigned)privateSensorData->CO2/5 & 0xff; // Mask lower 8
		unsigned char msb = (unsigned)privateSensorData->CO2/5 >> 8;   // Shift higher 8
		// Test-Code
		uint16_t merged=0;
		merged |=(uint16_t) lsb;
		merged |=(uint16_t) msb << 8;
		printf("%i: MERGED_BYTES \n",merged);
		loraPayload.bytes[CO2_LOW_PAYLOAD_INDEX]=lsb;
		loraPayload.bytes[CO2_HIGH_PAYLOAD_INDEX]=msb;
		loraPayload.bytes[TEMP_PAYLOAD_INDEX]=privateSensorData->temperature/5;
		loraPayload.bytes[HUMIDITY_PAYLOAD_INDEX]=privateSensorData->humidity/5;
		loraPayload.bytes[MOVEMENT_PAYLOAD_INDEX]=privateSensorData->movement/5;
		loraPayload.bytes[LIGHT_PAYLOAD_INDEX]=privateSensorData->light/5;
		printf("%dc,%dt,%dh,%ds,%dm PRE-REMOVE \n",privateSensorData->CO2/5,privateSensorData->temperature/5,privateSensorData->humidity/5,privateSensorData->light/5,privateSensorData->movement/5);
		e_LoRa_return_code_t returnCode;
		if ((returnCode = lora_driver_sent_upload_message(false, &loraPayload)) == LoRa_MAC_TX_OK )
		{
			printf("SENSOR_DATA_SEND_OFF\n");
			// The uplink message is sent and there is no downlink message received
		}
		else if (returnCode == LoRa_MAC_RX_OK)
		{
		    printf("%d:LORA_READ_OK \n",returnCode);
			parseMessage();
		}
		printf("%d:LORA RETURN CODE \n",returnCode);
		printf("%d:LSB,%d MSB",lsb,msb);
		privateSensorData->movement=0;
		privateSensorData->light=0;
		privateSensorData->humidity=0;
		privateSensorData->temperature=0;
		privateSensorData->CO2=0;
		printf("%dc,%dt,%dh,%ds,%dm POST-REMOVE \n",privateSensorData->CO2,privateSensorData->temperature,privateSensorData->humidity,privateSensorData->light,privateSensorData->movement);
		xSemaphoreGive(*privateSemaphore);
		vTaskDelayUntil(&xLastWakeTimeLoraSendOff,ONE_SECOND_SENSOR_TIMER*LORA_SECONDS_TO_WAIT+1);
	}
	#pragma clang diagnostic pop
}
//TODO discuss what does the device get back
void parseMessage(){
	printf("INPUT_RECEIVED \n");
}

void lora_timer_callback(TimerHandle_t pxTimer){
	printf("TIMER_FIRE\n");
	vTaskResume(ioTaskHandle);
}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void lora_setup(){
	lora_driver_reset_rn2483(1);
	vTaskDelay(2);
	lora_driver_reset_rn2483(0);
	vTaskDelay(150);
	if (lora_driver_rn2483_factory_reset() != LoRA_OK)
	{
		printf("FACTORY_RESET_FAILURE \n");
	}
	vTaskDelay(150);
	printf("CONFIGURE_START \n");
	vTaskDelay(150);
	if (lora_driver_configure_to_eu868() != LoRA_OK)
	{
		printf("CONFIGURE_BREAK \n");
	}
	static char dev_eui[17]; // It is static to avoid it to occupy stack space in the task
	if (lora_driver_get_rn2483_hweui(dev_eui) != LoRA_OK)
	{
		printf("HWUI_ERROR \n");
	}	else printf("%s, DEV_EUI \n",dev_eui);

	if (lora_driver_set_otaa_identity(LORA_appEUI,LORA_appKEY,dev_eui) != LoRA_OK)
	{
		printf("IDENTITY_BREAK \n");
	}
	e_LoRa_return_code_t rc;
	if ((rc=lora_driver_join(LoRa_OTAA)) == LoRa_ACCEPTED)
	{
		printf("LORA_ACCEPTED \n");
		}else if(rc==7){
		printf("LORA_DENIED_STARTING_RETRY\n");
		for (int i = 0; i < 5; ++i) {
			rc=lora_driver_join(LoRa_OTAA);
			switch(rc){
				case 7:{
					printf("LORA_DENIED_ATTEMPT:%i \n",i);
					continue;
				}
				case 8:{
					printf("LORA_ACCEPTED \n");
					return;
				}
				case 0:{
					printf("LORA_OK \n");
                    return;
				}
				case 3:{
					printf("LORA_NO_EMPTY_CHANNEL_TASK_TERMINATING... \n");
					vTaskSuspend(NULL);
					break;
				}
				case 1:{
					printf("LORA_ERROR_ATTEMPT:%i \n",i);
					continue;
				}
			}
            if(i==4){
                printf("CONNECTION_FAILED_TASK_TERMINATING...\n");
                vTaskSuspend(NULL);
            }
		}
	}
}
#pragma clang diagnostic pop