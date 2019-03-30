//
// Created by PC on 3/29/2019.
//

#include "LoraHelper.h"
#include <DataCollector.h>
#define LAURA_IO_TASK_PRIORITY (tskIDLE_PRIORITY+2)

static preferences_t* privatePreferences;
static SemaphoreHandle_t* privateSemaphore;
static sensor_data_t* privateSensorData;
static TaskHandle_t ioTaskHandle=NULL;
static TimerHandle_t lauraTimer;


// 5 minute delay in ticks
static const int IO_DELAY = (954/portTICK_PERIOD_MS)*300;

void lauraTimerCallback(TimerHandle_t pxTimer);


void initializeHelper(sensor_data_t* sensorData, SemaphoreHandle_t* semaphoreHandle,preferences_t* preferences){
    privatePreferences=preferences;
    privateSemaphore=semaphoreHandle;
    privateSensorData=sensorData;
    xTaskCreate(handleMessage,"MESSAGE_HANDLE",configMINIMAL_STACK_SIZE,NULL,LAURA_IO_TASK_PRIORITY,&ioTaskHandle);
    lauraTimer=xTimerCreate("SENSOR_TIMER",pdMS_TO_TICKS(IO_DELAY),pdTRUE,(void*)0,lauraTimerCallback);
    xTimerStart(lauraTimer,0);
}

void handleMessage(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    TickType_t xLastWakeTimeLoraSendOff=xTaskGetTickCount();
    while(1){
        //FIXME IMPLEMENT ME
        xSemaphoreTake(*privateSemaphore,IO_DELAY);
        printf("SENSOR_DATA_SEND_OFF %d\n",IO_DELAY);
        xSemaphoreGive(*privateSemaphore);
        vTaskDelayUntil(&xLastWakeTimeLoraSendOff,IO_DELAY);
    }
#pragma clang diagnostic pop
}

void parseMessage(){

}

void lauraTimerCallback(TimerHandle_t pxTimer){
    xSemaphoreGive(*privateSemaphore);
}
