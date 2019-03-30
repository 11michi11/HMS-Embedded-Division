
#ifndef SEP4_DEVICE_CODE_EVENTREACTOR_H
#define SEP4_DEVICE_CODE_EVENTREACTOR_H

#include <ATMEGA_FreeRTOS.h>
#include <io.h>
#include <ATMEGA_FreeRTOS.h>
#include <stdint-gcc.h>
#include <stdio.h>
#include <semphr.h>
#include <timers.h>

extern TaskHandle_t eventReactorTask;

typedef struct preferences{
    uint8_t  lightPreference;
    uint8_t  buzzerPreference;
}preferences_t;

void toggleLights();
void toggleBuzzer();
void initializeEventReactor(preferences_t* preferences);
#endif //SEP4_DEVICE_CODE_EVENTREACTOR_H
