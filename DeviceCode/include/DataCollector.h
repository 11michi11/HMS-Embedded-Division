#include <ATMEGA_FreeRTOS.h>
#include <stdint-gcc.h>
#include <stdio.h>
#include <semphr.h>
#include <timers.h>

#ifndef SEP4_DEVICE_CODE_DATACOLLECTOR_H
#define SEP4_DEVICE_CODE_DATACOLLECTOR_H

//FIXME Define final ports
#define PROXIMITY_PIN PINA
//FIXME Define final priority for sensors


//FIXME TASK HANDLES FOR SENSOR DATA (Put em in .C maybe? fuck do I know ask Ib)


typedef struct sensor_data{
    uint16_t CO2;
    uint16_t temperature;
    uint16_t light;
    uint16_t movement;
    uint16_t humidity;
}sensor_data_t;

void initialize_data_collector(sensor_data_t *sensorData, SemaphoreHandle_t *semaphoreHandle);
void gather_co2();
void gather_temp_and_humidity();
void gather_light();
void monitor_movement();

#endif //SEP4_DEVICE_CODE_DATACOLLECTOR_H
