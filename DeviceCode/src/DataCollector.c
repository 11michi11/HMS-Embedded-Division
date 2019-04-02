//
// Created by PC on 3/29/2019.
//

#include "DataCollector.h"
#include <util/delay.h>
#include <EventReactor.h>

//FIXME Define final ports

#define REGULAR_SENSOR_TASK_PRIORITY (tskIDLE_PRIORITY+1)
#define MOVEMENT_SENSOR_TASK_PRIORITY (tskIDLE_PRIORITY)
// ~1s
int const SENSOR_TIMER=954/portTICK_PERIOD_MS;

static sensor_data_t* sensorDataPrivate;
static SemaphoreHandle_t* semaphore;
static TaskHandle_t CO2Handle=NULL;
static TaskHandle_t TempHandle=NULL;
static TaskHandle_t SoundHandle=NULL;
static TaskHandle_t MovementHandle=NULL;

static TimerHandle_t sensorTimer;


void sensorTimerCallback(TimerHandle_t pxTimer);

void initializeDataCollector(sensor_data_t* sensorData, SemaphoreHandle_t* semaphoreHandle){
    sensorDataPrivate=sensorData;
    semaphore=semaphoreHandle;

    xTaskCreate(gatherCO2,"CO2_TASK",configMINIMAL_STACK_SIZE,NULL,REGULAR_SENSOR_TASK_PRIORITY,&CO2Handle);
    xTaskCreate(gatherTemp,"TEMP_TASK",configMINIMAL_STACK_SIZE,NULL,REGULAR_SENSOR_TASK_PRIORITY,&TempHandle);
    xTaskCreate(gatherSound,"SOUND_TASK",configMINIMAL_STACK_SIZE,NULL,REGULAR_SENSOR_TASK_PRIORITY,&SoundHandle);
    xTaskCreate(monitorMovement,"MOVEMENT_TASK",configMINIMAL_STACK_SIZE,NULL,MOVEMENT_SENSOR_TASK_PRIORITY,&MovementHandle);

    sensorTimer=xTimerCreate("SENSOR_TIMER",pdMS_TO_TICKS(1000),pdTRUE,(void*)0,sensorTimerCallback);
    xTimerStart(sensorTimer,0);

}

void gatherCO2(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    TickType_t xLastWakeTimeCO2=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*semaphore,SENSOR_TIMER*60);
        //FIXME IMPLEMENT ME
        printf("CO2 TASK %d \n",xLastWakeTimeCO2);
        xSemaphoreGive(*semaphore);
        vTaskDelayUntil(&xLastWakeTimeCO2,SENSOR_TIMER*60);
    }

#pragma clang diagnostic pop
}

void gatherTemp(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

    TickType_t xLastWakeTimeTemp=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*semaphore,SENSOR_TIMER*60);
        printf("TEMP TASK \n");
        xSemaphoreGive(*semaphore);
        vTaskDelayUntil(&xLastWakeTimeTemp,SENSOR_TIMER*60);
    }
#pragma clang diagnostic pop

}

void gatherSound(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

    TickType_t xLastWakeTimeSound=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*semaphore,SENSOR_TIMER*60);
        printf("SOUND TASK \n");
        //FIXME IMPLEMENT ME
        xSemaphoreGive(*semaphore);
        vTaskDelayUntil(&xLastWakeTimeSound,SENSOR_TIMER*60);
    }
#pragma clang diagnostic pop

}

void monitorMovement(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

    TickType_t xLastWakeTimeMovement=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*semaphore,SENSOR_TIMER);
        printf("MOVEMENT TASK \n");
        //FIXME Remove the following 3 lines as it's simply for testing purposes
        if(PROXIMITY_PIN==1){
            vTaskResume(eventReactorTask);
            xSemaphoreGive(*semaphore);
            vTaskDelayUntil(&xLastWakeTimeMovement,SENSOR_TIMER*10);
        } else{
            xSemaphoreGive(*semaphore);
            vTaskDelayUntil(&xLastWakeTimeMovement,SENSOR_TIMER*1);
        }
        //FIXME IMPLEMENT ME
    }
#pragma clang diagnostic pop
}

void sensorTimerCallback(TimerHandle_t pxTimer){
    xSemaphoreGive(*semaphore);
}
