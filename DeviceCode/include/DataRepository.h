#include <ATMEGA_FreeRTOS.h>
#include <stdint-gcc.h>
#include <stdio.h>
#include <semphr.h>
#include <timers.h>

#ifndef SEP4_DEVICE_CODE_DATACOLLECTOR_H
#define SEP4_DEVICE_CODE_DATACOLLECTOR_H
#define REGULAR_SENSOR_TASK_PRIORITY (tskIDLE_PRIORITY+2)
#define MOVEMENT_SENSOR_TASK_PRIORITY (tskIDLE_PRIORITY+1)
#define ONE_SECOND_SENSOR_TIMER (954/portTICK_PERIOD_MS)


typedef struct sensor_data{
    uint16_t CO2;
    uint16_t temperature;
    uint16_t light;
    uint16_t movement;
    uint16_t humidity;
}sensor_data_t;

void initialize_repository(sensor_data_t *sensorData, SemaphoreHandle_t *semaphoreHandle);

#endif //SEP4_DEVICE_CODE_DATACOLLECTOR_H
