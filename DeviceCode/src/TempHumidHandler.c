//
// Created by PC on 5/3/2019.
//

#include <hih8120.h>
#include "TempHumidHandler.h"
#include "DataRepository.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int const TH_SENSOR_TIMER=954/portTICK_PERIOD_MS;
static TaskHandle_t TempHandle=NULL;
static SemaphoreHandle_t* private_semaphore;
static uint16_t* private_temp_pointer;
static uint16_t* private_humid_pointer;


void th_handler_initialize(uint16_t* temp_pointer,uint16_t* humid_pointer,SemaphoreHandle_t *semaphoreHandle){
    private_temp_pointer=temp_pointer;
    private_humid_pointer=humid_pointer;
    private_semaphore=semaphoreHandle;
    xTaskCreate(th_task, "TEMP_TASK", configMINIMAL_STACK_SIZE, NULL, REGULAR_SENSOR_TASK_PRIORITY,
                &TempHandle);
    //--------------------------------------------- TEMP_HUMIDITY SENSOR SETUP --------------------------------------------------//
    if ( HIH8120_OK == hih8120Create() )
    {
        printf("TEMP_HUMIDITY_INITIALIZED \n");
    }
    //--------------------------------------------- TEMP_HUMIDITY SENSOR SETUP --------------------------------------------------//
}

void th_task(){
    TickType_t xLastWakeTimeTemp=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*private_semaphore,TH_SENSOR_TIMER*120);
        hih8120DriverReturnCode_t rc;

        rc=hih8120Wakeup();
        printf("HIH_WAKE_UP:%i\n",rc);
        vTaskDelay(pdMS_TO_TICKS(51));
        rc= hih8120Meassure();
        printf("HIH_MEASURE:%i\n",rc);


        *private_temp_pointer+=hih8120GetTemperature_x10()/10;
        *private_humid_pointer+=hih8120GetHumidityPercent_x10()/10;
        printf("%i:TEMP:%i:HUMID \n",*private_temp_pointer,*private_humid_pointer);
        printf("%i:TEMP:%i:HUMID \n",hih8120GetTemperature_x10()/10,hih8120GetHumidityPercent_x10()/10);
        xSemaphoreGive(*private_semaphore);
        vTaskDelayUntil(&xLastWakeTimeTemp,TH_SENSOR_TIMER*60);
    }
}
#pragma clang diagnostic pop