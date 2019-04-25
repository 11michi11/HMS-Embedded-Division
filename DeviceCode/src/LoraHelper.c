#include "LoraHelper.h"
#include <DataCollector.h>
#include <ihal.h>
#include <lora_driver.h>
#include <util/delay.h>


#define LORA_IO_TASK_PRIORITY (tskIDLE_PRIORITY+2)

#define LORA_appEUI "E81068FC10812076"
#define LORA_appKEY "3894B87078D8A38B56E419ABCA16043E"

#define CO2_LOW_PAYLOAD_INDEX 0
#define CO2_HIGH_PAYLOAD_INDEX 1
#define TEMP_PAYLOAD_INDEX 2
#define HUMIDITY_PAYLOAD_INDEX 3
#define SOUND_PAYLOAD_INDEX 4
#define MOVEMENT_PAYLOAD_INDEX 5
#define LIGHT_PAYLOAD_INDEX 6
#define LORA_INIT_TASK_PRIORITY 7

static preferences_t* privatePreferences;
static SemaphoreHandle_t* privateSemaphore;
static sensor_data_t* privateSensorData;
static TaskHandle_t ioTaskHandle=NULL;
static TimerHandle_t loraTimer;
static TaskHandle_t loraInitTask;


// 5 minute delay in ticks
static const int IO_DELAY = (954/portTICK_PERIOD_MS)*300;

void lora_timer_callback(TimerHandle_t pxTimer);
void lora_setup();

void initialize_lora_helper(sensor_data_t *sensorData, SemaphoreHandle_t *semaphoreHandle, preferences_t *preferences){
    privatePreferences=preferences;
    privateSemaphore=semaphoreHandle;
    privateSensorData=sensorData;

    xTaskCreate(handle_message, "MESSAGE_HANDLE", configMINIMAL_STACK_SIZE, NULL, LORA_IO_TASK_PRIORITY, &ioTaskHandle);
    xTaskCreate(lora_setup, "MESSAGE_HANDLE", configMINIMAL_STACK_SIZE, NULL, LORA_IO_TASK_PRIORITY, &loraInitTask);

    hal_create(LORA_INIT_TASK_PRIORITY+1);
    lora_driver_create(ser_USART1);

   vTaskSuspend(ioTaskHandle);
   loraTimer= xTimerCreate("SENSOR_TIMER", IO_DELAY, pdFALSE, (void *) 0, lora_timer_callback);
   xTimerStart(loraTimer,0);
}

void handle_message(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    TickType_t xLastWakeTimeLoraSendOff=xTaskGetTickCount();
    while(1){
        //FIXME IMPLEMENT ME
        xSemaphoreTake(*privateSemaphore,IO_DELAY);
        lora_payload_t loraPayload;
        loraPayload.len=7;
        // Separating
        unsigned char lsb = (unsigned)privateSensorData->CO2 & 0xff; // Mask lower 8
        unsigned char msb = (unsigned)privateSensorData->CO2 >> 8;   // Shift higher 8 bits
        loraPayload.bytes[CO2_LOW_PAYLOAD_INDEX]=lsb;
        loraPayload.bytes[CO2_HIGH_PAYLOAD_INDEX]=msb;
        loraPayload.bytes[TEMP_PAYLOAD_INDEX]=privateSensorData->temperature/5;
        loraPayload.bytes[HUMIDITY_PAYLOAD_INDEX]=privateSensorData->humidity/5;
        loraPayload.bytes[MOVEMENT_PAYLOAD_INDEX]=privateSensorData->movement/5;
        loraPayload.bytes[SOUND_PAYLOAD_INDEX]=privateSensorData->sound/5;
        printf("%dc,%dt,%dh,%ds,%dm PRE-REMOVE \n",privateSensorData->CO2/5,privateSensorData->temperature/5,privateSensorData->humidity/5,privateSensorData->sound/5,privateSensorData->movement/5);
        e_LoRa_return_code_t returnCode;
        if ((returnCode = lora_driver_sent_upload_message(false, &loraPayload)) == LoRa_MAC_TX_OK )
        {
            printf("SENSOR_DATA_SEND_OFF %d\n",IO_DELAY);
            // The uplink message is sent and there is no downlink message received
        }
        else if (returnCode == LoRa_MAC_RX_OK)
        {
            parseMessage();
        }
		printf("%d:LORA RETURN CODE \n",returnCode);
		printf("%d:LSB,%d MSB",lsb,msb);
        privateSensorData->movement=0;
        privateSensorData->sound=0;
        privateSensorData->humidity=0;
        privateSensorData->temperature=0;
        privateSensorData->CO2=0;
        printf("%dc,%dt,%dh,%ds,%dm POST-REMOVE",privateSensorData->CO2,privateSensorData->temperature,privateSensorData->humidity,privateSensorData->sound,privateSensorData->movement);
        xSemaphoreGive(*privateSemaphore);
        vTaskDelayUntil(&xLastWakeTimeLoraSendOff,IO_DELAY);
    }
#pragma clang diagnostic pop
}
//TODO discuss what does the device get back
void parseMessage(){

}

void lora_timer_callback(TimerHandle_t pxTimer){
    printf("TIMER_FIRE\n");
    vTaskResume(ioTaskHandle);
}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void lora_setup(){
	while(1){
		xSemaphoreTake(*privateSemaphore,5000);
		lora_driver_reset_rn2483(1);
		vTaskDelay(2);
		lora_driver_reset_rn2483(0);
		vTaskDelay(150);
		if (lora_driver_configure_to_eu868() != LoRA_OK)
		{
            printf("CONFIGURE_BREAK \n");
		}
        static char dev_eui[17]; // It is static to avoid it to occupy stack space in the task
        if (lora_driver_get_rn2483_hweui(dev_eui) != LoRA_OK)
        {
            printf("HWUI_ERROR \n");
        }
        if (lora_driver_set_otaa_identity(LORA_appEUI,LORA_appKEY,dev_eui) != LoRA_OK)
        {
            printf("IDENTITY_BREAK \n");
        }
        printf("%s, TACO TUESDAY \n",dev_eui);
		xSemaphoreGive(*privateSemaphore);
		vTaskDelete(NULL);
			}

}
#pragma clang diagnostic pop
