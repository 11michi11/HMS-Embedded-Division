//
// Created by PC on 5/3/2019.
//

#include <DataRepository.h>
#include <hcSr501.h>
#include <EventReactor.h>
#include "MovementHandler.h"

#define LIGHT_TURN_ON_TIMER_IN_SECONDS 20

static TaskHandle_t MovementHandle=NULL;
static hcSr501_p hcSr501Inst=NULL;
static uint16_t* private_movement_pointer;
static SemaphoreHandle_t* private_semaphore;


void movement_handler_initialize(uint16_t* movement_pointer, SemaphoreHandle_t *semaphoreHandle){
      private_semaphore=semaphoreHandle;
      private_movement_pointer=movement_pointer;
    //--------------------------------------------- MOVEMENT SENSOR SETUP --------------------------------------------------//
        hcSr501Inst = hcSr501Create(&PORTE, PE5);
        if ( NULL != hcSr501Inst )
        {
            printf("MOVEMENT_DRIVER_INITIALIZED \n");
        }
        //--------------------------------------------- MOVEMENT SENSOR SETUP --------------------------------------------------//
        xTaskCreate(movement_task, "MOVEMENT_TASK", configMINIMAL_STACK_SIZE, NULL, MOVEMENT_SENSOR_TASK_PRIORITY,&MovementHandle);
}

void movement_task(){
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wmissing-noreturn"
	TickType_t xLastWakeTimeMovement=xTaskGetTickCount();
	while(1){
		xSemaphoreTake(*private_semaphore,ONE_SECOND_SENSOR_TIMER);
		printf("MOVEMENT TASK \n");
		if ( hcSr501IsDetecting(hcSr501Inst) )
		{
			*private_movement_pointer+=1;
			printf("MOVEMENT_DETECTED\n");
			xSemaphoreGive(*private_semaphore);
			toggleLights();
            vTaskDelay(ONE_SECOND_SENSOR_TIMER*LIGHT_TURN_ON_TIMER_IN_SECONDS);
            toggleLights();
			vTaskDelayUntil(&xLastWakeTimeMovement,ONE_SECOND_SENSOR_TIMER*LIGHT_TURN_ON_TIMER_IN_SECONDS);
		}
		else
		{
			xSemaphoreGive(*private_semaphore);
			vTaskDelayUntil(&xLastWakeTimeMovement,ONE_SECOND_SENSOR_TIMER*1);
		}
	}
	#pragma clang diagnostic pop
}