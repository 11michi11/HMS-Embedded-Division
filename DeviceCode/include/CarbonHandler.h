//
// Created by PC on 5/3/2019.
//

#ifndef DEVICECODE_CARBON_HANDLER_H
#define DEVICECODE_CARBON_HANDLER_H


#include <ATMEGA_FreeRTOS.h>
#include <stdint-gcc.h>
#include <stdio.h>
#include <semphr.h>


void carbon_handler_initialize(uint16_t* co2_pointer,SemaphoreHandle_t *semaphoreHandle);
void co2_task();
void co2_callback(uint16_t co2_ppm);


#endif //DEVICECODE_CARBON_HANDLER_H
