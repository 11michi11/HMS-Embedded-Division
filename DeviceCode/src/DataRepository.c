//
// Created by PC on 3/29/2019.
//

#include "DataRepository.h"
#include <util/delay.h>
#include <EventReactor.h>
#include <stdlib.h>
#include <time.h>
#include <hcSr501.h>
#include <mh_z19.h>
#include <serial.h>
#include <hih8120.h>
#include <tsl2591.h>
#include <LightHandler.h>
#include <MovementHandler.h>
#include "TempHumidHandler.h"
#include "CarbonHandler.h"

static sensor_data_t* sensorDataPrivate;
static SemaphoreHandle_t* semaphore;

void initialize_repository(sensor_data_t *sensorData, SemaphoreHandle_t *semaphoreHandle){
    sensorDataPrivate=sensorData;
    semaphore=semaphoreHandle;
    //--------------------------------------------- CLEAN STATE SETUP --------------------------------------------------//
    sensorDataPrivate->CO2=0;
    sensorDataPrivate->humidity=0;
    sensorDataPrivate->movement=0;
    sensorDataPrivate->light=0;
    sensorDataPrivate->temperature=0;
    //--------------------------------------------- TASK AND TIMER SETUP --------------------------------------------------//
    carbon_handler_initialize(&sensorDataPrivate->CO2,semaphoreHandle);
    th_handler_initialize(&sensorDataPrivate->temperature,&sensorDataPrivate->humidity,semaphoreHandle);
    light_handler_initialize(&sensorDataPrivate->light,semaphoreHandle);
    movement_handler_initialize(&sensorDataPrivate->movement,semaphoreHandle);
}





