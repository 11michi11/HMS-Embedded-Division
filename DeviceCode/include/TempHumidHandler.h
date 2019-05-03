//
// Created by PC on 5/3/2019.
//

#ifndef DEVICECODE_TEMPHUMIDHANDLER_H
#define DEVICECODE_TEMPHUMIDHANDLER_H


#include <ATMEGA_FreeRTOS.h>
#include <stdint-gcc.h>
#include <stdio.h>
#include <semphr.h>
#include <timers.h>

void th_handler_initialize(uint16_t* temp_pointer,uint16_t* humid_pointer,SemaphoreHandle_t *semaphoreHandle);
void th_task();

#endif //DEVICECODE_TEMPHUMIDHANDLER_H
