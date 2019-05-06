//
// Created by PC on 5/3/2019.
//

#include <DataRepository.h>
#include <hcSr501.h>
#include <EventReactor.h>
#include "MovementHandler.h"

static TaskHandle_t MovementHandle=NULL;
static hcSr501_p hcSr501Inst=NULL;
static uint16_t* private_movement_pointer;
static SemaphoreHandle_t* private_semaphore;
int const MOVEMENT_SENSOR_TIMER=954/portTICK_PERIOD_MS;


void movement_handler_initialize(uint16_t* movement_pointer, SemaphoreHandle_t *semaphoreHandle){
      private_semaphore=semaphoreHandle;
      private_movement_pointer=movement_pointer;
    //--------------------------------------------- MOVEMENT SENSOR SETUP --------------------------------------------------//
        hcSr501Inst = hcSr501Create(&PORTE, PE5);
        if ( NULL != hcSr501Inst )
        {
            printf("DRIVER_INITIALIZED \n");
        }
        //--------------------------------------------- MOVEMENT SENSOR SETUP --------------------------------------------------//
        xTaskCreate(movement_task, "MOVEMENT_TASK", configMINIMAL_STACK_SIZE, NULL, MOVEMENT_SENSOR_TASK_PRIORITY,&MovementHandle);
}

void movement_task(){
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wmissing-noreturn"

	TickType_t xLastWakeTimeMovement=xTaskGetTickCount();
	while(1){
		xSemaphoreTake(*private_semaphore,MOVEMENT_SENSOR_TIMER);
		printf("MOVEMENT TASK \n");
		if ( hcSr501IsDetecting(hcSr501Inst) )
		{
			*private_movement_pointer+=1;
			printf("MOVEMENT_DETECTED\n");
			toggleLights();
			vTaskDelayUntil(&xLastWakeTimeMovement,MOVEMENT_SENSOR_TIMER*10);
			xSemaphoreGive(*private_semaphore);
		}
		else
		{
			xSemaphoreGive(*private_semaphore);
			vTaskDelayUntil(&xLastWakeTimeMovement,MOVEMENT_SENSOR_TIMER*1);
		}
	}
	#pragma clang diagnostic pop
}