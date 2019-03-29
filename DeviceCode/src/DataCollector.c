//
// Created by PC on 3/29/2019.
//

#include "DataCollector.h"
#include <util/delay.h>

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




void initializeDataCollector(sensor_data_t* sensorData, SemaphoreHandle_t* semaphoreHandle){
    sensorDataPrivate=sensorData;
    semaphore=semaphoreHandle;

    xTaskCreate(gatherCO2,"CO2_TASK",configMINIMAL_STACK_SIZE,NULL,REGULAR_SENSOR_TASK_PRIORITY,&CO2Handle);
    xTaskCreate(gatherTemp,"TEMP_TASK",configMINIMAL_STACK_SIZE,NULL,REGULAR_SENSOR_TASK_PRIORITY,&TempHandle);
    xTaskCreate(gatherSound,"SOUND_TASK",configMINIMAL_STACK_SIZE,NULL,REGULAR_SENSOR_TASK_PRIORITY,&SoundHandle);
    xTaskCreate(monitorMovement,"MOVEMENT_TASK",configMINIMAL_STACK_SIZE,NULL,MOVEMENT_SENSOR_TASK_PRIORITY,&MovementHandle);

}

void gatherCO2(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    TickType_t xLastWakeTimeCO2=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*semaphore,portMAX_DELAY);
        //FIXME IMPLEMENT ME
        printf("CO2 TASK \n");
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
        xSemaphoreTake(*semaphore,portMAX_DELAY);
        printf("TEMP TASK \n");
        xSemaphoreGive(*semaphore);
        vTaskDelayUntil(&xLastWakeTimeTemp,SENSOR_TIMER*60);
    }
#pragma clang diagnostic pop

}

void gatherSound(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(1){
        TickType_t xLastWakeTimeSound=xTaskGetTickCount();
        xSemaphoreTake(*semaphore,portMAX_DELAY);
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
    while(1){
        TickType_t xLastWakeTimeSound=xTaskGetTickCount();
        xSemaphoreTake(*semaphore,SENSOR_TIMER*60);
        printf("MOVEMENT TASK \n");
        xSemaphoreGive(*semaphore);
        vTaskDelayUntil(&xLastWakeTimeSound,SENSOR_TIMER);
        //FIXME IMPLEMENT ME
    }
#pragma clang diagnostic pop

}
sensor_data_t* getSensorData(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(1){
        //FIXME IMPLEMENT ME
        TickType_t xLastWakeTimeSound=xTaskGetTickCount();
        xSemaphoreTake(*semaphore,portMAX_DELAY);
        printf("SENSOR DATA GATHERED \n");
        xSemaphoreGive(*semaphore);
        vTaskDelayUntil(&xLastWakeTimeSound,SENSOR_TIMER*61);
    }
#pragma clang diagnostic pop

}
