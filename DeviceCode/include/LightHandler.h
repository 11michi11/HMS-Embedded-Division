//
// Created by PC on 5/3/2019.
//

#ifndef DEVICECODE_LIGHTHANDLER_H
#define DEVICECODE_LIGHTHANDLER_H

#include <ATMEGA_FreeRTOS.h>
#include <stdint-gcc.h>
#include <stdio.h>
#include <semphr.h>
#include <tsl2591.h>


void light_handler_initialize(uint16_t* light_pointer,SemaphoreHandle_t *semaphoreHandle);
void light_task();
void light_callback(tsl2591ReturnCode_t rc);


#endif //DEVICECODE_LIGHTHANDLER_H
