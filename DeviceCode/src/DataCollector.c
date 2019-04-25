//
// Created by PC on 3/29/2019.
//

#include "DataCollector.h"
#include <util/delay.h>
#include <EventReactor.h>
#include <stdlib.h>
#include <time.h>
#include <hcSr501.h>
#include <mh_z19.h>
#include <serial.h>
#include <hih8120.h>

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
static hcSr501_p hcSr501Inst=NULL;

static TimerHandle_t sensorTimer;

void sensorTimerCallback(TimerHandle_t pxTimer);
void co2_callback(uint16_t co2_ppm);

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

    //--------------------------------------------- MOVEMENT SENSOR SETUP --------------------------------------------------//
    hcSr501Inst = hcSr501Create(&PORTE, PE5);
    if ( NULL != hcSr501Inst )
    {
        printf("DRIVER_INITIALIZED");
    }
    //--------------------------------------------- CO_2 SENSOR SETUP --------------------------------------------------//
    mh_z19_create(ser_USART3, co2_callback);
    //--------------------------------------------- TEMP_HUMIDITY SENSOR SETUP --------------------------------------------------//
    if ( HIH8120_OK == hih8120Create() )
    {
        printf("TEMP_HUMIDITY_INITIALIZED /n");
    }

}

void gatherCO2(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    TickType_t xLastWakeTimeCO2=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*semaphore,SENSOR_TIMER*60);
        //FIXME IMPLEMENT ME
        printf("CO2 TASK %d \n",xLastWakeTimeCO2);
        mh_z19_return_code_t rc;
        rc = mh_z19_take_meassuring();
        if (rc != 0)
        {
            printf("CO2_SENSOR_ERROR\n");
        }
        xSemaphoreGive(*semaphore);
        vTaskDelayUntil(&xLastWakeTimeCO2,SENSOR_TIMER*20);
    }

#pragma clang diagnostic pop
}

void gatherTempAndHumidity(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    TickType_t xLastWakeTimeTemp=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*semaphore,SENSOR_TIMER*60);

        if ( HIH8120_OK != hih8120Wakeup() )
        {
            printf("WAKE_UP_FAILED\n");
        }

        vTaskDelay(pdMS_TO_TICKS(100));
        if ( HIH8120_OK !=  hih8120Meassure() )
        {
            printf("MEASURE_FAILED\n");
        }

        float humidity = 0.0;
        float temperature = 0.0;
        humidity = hih8120GetHumidity();
        temperature = hih8120GetTemperature();
        uint8_t *array;
        array = (uint8_t*)(&temperature);
        printf("%i:%i:%i:%i \n",array[0],array[1],array[2],array[3]);
        printf("%.2f:TEMP\n",temperature);
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
        if ( hcSr501IsDetecting(hcSr501Inst) )
        {
            sensorDataPrivate->movement+=1;
            printf("MOVEMENT_DETECTED\n");
            vTaskResume(eventReactorTask);
            xSemaphoreGive(*semaphore);
            vTaskDelayUntil(&xLastWakeTimeMovement,SENSOR_TIMER*10);
        }
        else
        {
            xSemaphoreGive(*semaphore);
            vTaskDelayUntil(&xLastWakeTimeMovement,SENSOR_TIMER*1);
        }
        //FIXME IMPLEMENT ME
    }
#pragma clang diagnostic pop
}

void co2_callback(uint16_t co2_ppm){
    sensorDataPrivate->CO2=sensorDataPrivate->CO2+co2_ppm;
    printf("%i CO2_DATA \n",sensorDataPrivate->CO2);
}

void sensorTimerCallback(TimerHandle_t pxTimer){
    xSemaphoreGive(*semaphore);
}
