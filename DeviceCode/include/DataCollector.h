//
// Created by PC on 3/29/2019.
//
#include <ATMEGA_FreeRTOS.h>
#include <stdint-gcc.h>
#include <stdio.h>
#include <semphr.h>
#include <timers.h>

#ifndef SEP4_DEVICE_CODE_DATACOLLECTOR_H
#define SEP4_DEVICE_CODE_DATACOLLECTOR_H

//FIXME Define final ports
#define CO2_PORT PA3;
#define TEMP_PORT PA2;
#define SOUND_PORT PA1;
#define PROXIMITY_PORT PA0;
//FIXME Define final priority for sensors
#define REGULAR_SENSOR_PRIORITY (IDLE)

//FIXME TASK HANDLES FOR SENSOR DATA (Put em in .C maybe? fuck do I know ask Ib)


typedef struct sensor_data{
    uint8_t CO2;
    uint8_t temperature;
    uint8_t sound;
    uint8_t movement;
}sensor_data_t;

void initializeDataCollector(sensor_data_t* sensorData, SemaphoreHandle_t* semaphoreHandle);
void gatherCO2();
void gatherTemp();
void gatherSound();
void monitorMovement();
sensor_data_t* getSensorData();

#endif //SEP4_DEVICE_CODE_DATACOLLECTOR_H
