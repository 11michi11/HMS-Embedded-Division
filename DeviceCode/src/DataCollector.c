//
// Created by PC on 3/29/2019.
//

#include "DataCollector.h"
#include <util/delay.h>
#include <EventReactor.h>
#include <stdlib.h>
#include <time.h>

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
    xTaskCreate(gatherTempAndHumidity, "TEMP_TASK", configMINIMAL_STACK_SIZE, NULL, REGULAR_SENSOR_TASK_PRIORITY,
                &TempHandle);
    xTaskCreate(gatherSound,"SOUND_TASK",configMINIMAL_STACK_SIZE,NULL,REGULAR_SENSOR_TASK_PRIORITY,&SoundHandle);
    xTaskCreate(monitorMovement,"MOVEMENT_TASK",configMINIMAL_STACK_SIZE,NULL,MOVEMENT_SENSOR_TASK_PRIORITY,&MovementHandle);

    sensorTimer=xTimerCreate("SENSOR_TIMER",pdMS_TO_TICKS(1000),pdTRUE,(void*)0,sensorTimerCallback);
    xTimerStart(sensorTimer,0);

    //FIXME REMOVE IN FINAL
    srand(time(NULL));

    //TODO Replace me with CO2 Sensor initiliazer
    //TODO replace me with Temp Sensor initializer
    //TODO replace me with movement sensor initializer

}

void gatherCO2(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    TickType_t xLastWakeTimeCO2=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*semaphore,SENSOR_TIMER*60);
        //FIXME IMPLEMENT ME
        printf("CO2 TASK %d \n",xLastWakeTimeCO2);
        sensorDataPrivate->CO2+=rand()%1000;
        xSemaphoreGive(*semaphore);
        vTaskDelayUntil(&xLastWakeTimeCO2,SENSOR_TIMER*60);
    }

#pragma clang diagnostic pop
}

void gatherTempAndHumidity(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    TickType_t xLastWakeTimeTemp=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*semaphore,SENSOR_TIMER*60);
        printf("SENSOR_WAKE_UP\n");
        vTaskDelay(pdMS_TO_TICKS(100));
        sensorDataPrivate->temperature+=rand()%25;
        sensorDataPrivate->temperature+=rand()%159;
        printf("SENSOR_WOKE_UP \n");
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
        sensorDataPrivate->temperature+=rand()%200;
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
        int random=rand()%10;
        if(random>5){
            sensorDataPrivate->movement++;
        }
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

void co2_callback(uint16_t co2_ppm){
    sensorDataPrivate->CO2=co2_ppm;
}

void sensorTimerCallback(TimerHandle_t pxTimer){
    xSemaphoreGive(*semaphore);
}
