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
#include <tsl2591.h>

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

void sensor_timer_callback(TimerHandle_t pxTimer);
void co2_callback(uint16_t co2_ppm);
void light_callback(tsl2591ReturnCode_t rc);

void initialize_data_collector(sensor_data_t *sensorData, SemaphoreHandle_t *semaphoreHandle){
    sensorDataPrivate=sensorData;
    semaphore=semaphoreHandle;
    //--------------------------------------------- CLEAN STATE SETUP --------------------------------------------------//
    sensorDataPrivate->CO2=0;
    sensorDataPrivate->humidity=0;
    sensorDataPrivate->movement=0;
    sensorDataPrivate->light=0;
    sensorDataPrivate->temperature=0;

    //--------------------------------------------- TASK AND TIMER SETUP --------------------------------------------------//

    xTaskCreate(gather_co2, "CO2_TASK", configMINIMAL_STACK_SIZE, NULL, REGULAR_SENSOR_TASK_PRIORITY, &CO2Handle);
    xTaskCreate(gather_temp_and_humidity, "TEMP_TASK", configMINIMAL_STACK_SIZE, NULL, REGULAR_SENSOR_TASK_PRIORITY,
                &TempHandle);
    xTaskCreate(gather_light, "SOUND_TASK", configMINIMAL_STACK_SIZE, NULL, REGULAR_SENSOR_TASK_PRIORITY, &SoundHandle);
    xTaskCreate(monitor_movement, "MOVEMENT_TASK", configMINIMAL_STACK_SIZE, NULL, MOVEMENT_SENSOR_TASK_PRIORITY,
                &MovementHandle);
    //FIXME Still need to figure out where to use this one.
    sensorTimer= xTimerCreate("SENSOR_TIMER", pdMS_TO_TICKS(1000), pdTRUE, (void *) 0, sensor_timer_callback);
    xTimerStart(sensorTimer,0);

    //--------------------------------------------- MOVEMENT SENSOR SETUP --------------------------------------------------//
    hcSr501Inst = hcSr501Create(&PORTE, PE5);
    if ( NULL != hcSr501Inst )
    {
        printf("DRIVER_INITIALIZED \n");
    }
    //--------------------------------------------- MOVEMENT SENSOR SETUP --------------------------------------------------//

    //--------------------------------------------- CO_2 SENSOR SETUP --------------------------------------------------//
    mh_z19_create(ser_USART3, co2_callback);
    //--------------------------------------------- CO_2 SENSOR SETUP --------------------------------------------------//

    //--------------------------------------------- TEMP_HUMIDITY SENSOR SETUP --------------------------------------------------//
    if ( HIH8120_OK == hih8120Create() )
    {
        printf("TEMP_HUMIDITY_INITIALIZED \n");
    }
    //--------------------------------------------- TEMP_HUMIDITY SENSOR SETUP --------------------------------------------------//

    //--------------------------------------------- LIGHT SENSOR SETUP --------------------------------------------------//
    tsl2591Create(light_callback);
    //--------------------------------------------- LIGHT SENSOR SETUP --------------------------------------------------//
}

void gather_co2(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    TickType_t xLastWakeTimeCO2=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*semaphore,SENSOR_TIMER*60);
        printf("CO2 TASK %d \n",xLastWakeTimeCO2);
        mh_z19_return_code_t rc;
        rc = mh_z19_take_meassuring();
        if (rc != 0)
        {
            printf("CO2_SENSOR_ERROR\n");
        }
        xSemaphoreGive(*semaphore);
        vTaskDelayUntil(&xLastWakeTimeCO2,SENSOR_TIMER*60);
    }
#pragma clang diagnostic pop
}

void gather_temp_and_humidity(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    TickType_t xLastWakeTimeTemp=xTaskGetTickCount();
    while(1){
        //FIXME Ask Ib about the status codes that are returned Measure / WakeUp
        xSemaphoreTake(*semaphore,SENSOR_TIMER*120);
        printf("HIH_WAKE_UP\n");
        hih8120Wakeup();
        vTaskDelayUntil(&xLastWakeTimeTemp,pdMS_TO_TICKS(51));
        printf("HIH_MEASURE\n");

        hih8120Meassure();
        vTaskDelayUntil(&xLastWakeTimeTemp,pdMS_TO_TICKS(51));

        sensorDataPrivate->temperature+=hih8120GetTemperature_x10()/10;
        sensorDataPrivate->humidity+=hih8120GetHumidityPercent_x10()/10;

        printf("%i:TEMP:%i:HUMID \n",sensorDataPrivate->temperature,sensorDataPrivate->humidity);
        xSemaphoreGive(*semaphore);
        vTaskDelayUntil(&xLastWakeTimeTemp,SENSOR_TIMER*60);
    }
#pragma clang diagnostic pop

}

void gather_light(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    TickType_t xLastWakeTimeLight=xTaskGetTickCount();
    while(1){
        //FIXME SWAP TO LUX WHEN IT'S ACTUALLY IMPLEMENTED
        printf("LIGHT TASK \n");
        xSemaphoreTake(*semaphore,SENSOR_TIMER*60);
        tsl2591Enable();
        vTaskDelay(150);
        tsl2591FetchData();
        vTaskDelay(150);
        uint16_t light;
        tsl2591GetVisibleRaw(&light);
        vTaskDelay(150);
        printf("%i:VISIBLE LIGHT \n",light);
        sensorDataPrivate->light+=light;
        tsl2591Disable();
        xSemaphoreGive(*semaphore);
        vTaskDelayUntil(&xLastWakeTimeLight,SENSOR_TIMER*60);
    }
#pragma clang diagnostic pop

}

void monitor_movement(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

    TickType_t xLastWakeTimeMovement=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*semaphore,SENSOR_TIMER);
        printf("MOVEMENT TASK \n");
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
    }
#pragma clang diagnostic pop
}

void co2_callback(uint16_t co2_ppm){
    sensorDataPrivate->CO2=sensorDataPrivate->CO2+co2_ppm;
    printf("%i CO2_DATA \n",sensorDataPrivate->CO2);
}

void sensor_timer_callback(TimerHandle_t pxTimer){
    xSemaphoreGive(*semaphore);
}

void light_callback(tsl2591ReturnCode_t rc){
    printf("%i:RETURN CODE\n",rc);
}