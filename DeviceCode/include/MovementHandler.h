//
// Created by PC on 5/3/2019.
//

#ifndef DEVICECODE_MOVEMENTHANDLER_H
#define DEVICECODE_MOVEMENTHANDLER_H

#include <stdint-gcc.h>
#include <semphr.h>

void movement_handler_initialize(uint16_t* movement_pointer, SemaphoreHandle_t *semaphoreHandle);
void movement_task();

#endif //DEVICECODE_MOVEMENTHANDLER_H
