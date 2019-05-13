//
// Created by PC on 5/3/2019.
//

#include <tsl2591.h>
#include <DataRepository.h>
#include "LightHandler.h"

#define LIGHT_SECONDS_TO_WAIT 60


static uint16_t* private_light_pointer;
static SemaphoreHandle_t* private_semaphore;
static TaskHandle_t LightHandle=NULL;


void light_handler_initialize(uint16_t* light_pointer,SemaphoreHandle_t *semaphoreHandle){
        xTaskCreate(light_task, "SOUND_TASK", configMINIMAL_STACK_SIZE, NULL, REGULAR_SENSOR_TASK_PRIORITY, &LightHandle);
        private_light_pointer=light_pointer;
        private_semaphore=semaphoreHandle;
        //--------------------------------------------- LIGHT SENSOR SETUP --------------------------------------------------//
        tsl2591Create(light_callback);
        //--------------------------------------------- LIGHT SENSOR SETUP --------------------------------------------------//
}

void light_task(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    TickType_t xLastWakeTimeLight=xTaskGetTickCount();
    while(1){
        printf("LIGHT TASK \n");
        xSemaphoreTake(*private_semaphore,ONE_SECOND_SENSOR_TIMER*LIGHT_SECONDS_TO_WAIT);
        if(tsl2591Enable()==7){
            printf("LIGHT_DRIVER_NOT_INITIALIZED_TASK_TERMINATING...\n");
			xSemaphoreGive(*private_semaphore);
            vTaskSuspend(NULL);
        }
        vTaskDelay(150);
        tsl2591FetchData();
        vTaskDelay(150);
        tsl2591Disable();
        vTaskDelay(150);
        xSemaphoreGive(*private_semaphore);
        vTaskDelayUntil(&xLastWakeTimeLight,ONE_SECOND_SENSOR_TIMER*LIGHT_SECONDS_TO_WAIT);
    }
#pragma clang diagnostic pop

}

void light_callback(tsl2591ReturnCode_t rc){
    uint16_t light;
    printf("%i:LIGHT_CALLBACK_RC\n", rc);
    switch (rc) {
        case TSL2591_DATA_READY: {
            if (TSL2591_OK == (rc = tsl2591GetVisibleRaw(&light))) {
                printf("VISIBLE_RAW_MEASURED:%i\n", light);
                *private_light_pointer+=light;
                printf("VISIBLE_RAW_ADDED:%i\n", *private_light_pointer);
            }
            break;
        }
        case TSL2591_BUSY:{
            vTaskDelay(pdMS_TO_TICKS(100));
            tsl2591FetchData();
            break;
        }
    }
}