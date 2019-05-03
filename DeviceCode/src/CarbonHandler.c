

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

#include "CarbonHandler.h"
#include "DataRepository.h"
#include <util/delay.h>
#include <EventReactor.h>
#include <stdlib.h>
#include <time.h>
#include <mh_z19.h>


static uint16_t* private_co2_pointer;
static SemaphoreHandle_t* private_semaphore;
static TaskHandle_t CO2Handle=NULL;
int const CO2_SENSOR_TIMER=954/portTICK_PERIOD_MS;


void carbon_handler_initialize(uint16_t* co2_pointer,SemaphoreHandle_t* semaphoreHandle){
    private_co2_pointer=co2_pointer;
    private_semaphore=semaphoreHandle;
    xTaskCreate(co2_task, "CO2_TASK",
            configMINIMAL_STACK_SIZE, NULL, REGULAR_SENSOR_TASK_PRIORITY,&CO2Handle);
    //--------------------------------------------- CO_2 SENSOR SETUP --------------------------------------------------//
    mh_z19_create(ser_USART3, co2_callback);
    //--------------------------------------------- CO_2 SENSOR SETUP --------------------------------------------------//
}

void co2_task(){
    TickType_t xLastWakeTimeCO2=xTaskGetTickCount();
    while(1){
        xSemaphoreTake(*private_semaphore,CO2_SENSOR_TIMER*60);
        printf("CO2 TASK %d \n",xLastWakeTimeCO2);
        mh_z19_return_code_t rc;
        rc = mh_z19_take_meassuring();
        if (rc != 0)
        {
            printf("CO2_SENSOR_ERROR\n");
        }
        xSemaphoreGive(*private_semaphore);
        vTaskDelayUntil(&xLastWakeTimeCO2,CO2_SENSOR_TIMER*60);
    }
}

void co2_callback(uint16_t co2_ppm){
    *private_co2_pointer+=co2_ppm;
    printf("%i CO2_DATA \n",*private_co2_pointer);
}

#pragma clang diagnostic pop