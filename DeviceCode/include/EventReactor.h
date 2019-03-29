//
// Created by PC on 3/29/2019.
//

#ifndef SEP4_DEVICE_CODE_EVENTREACTOR_H
#define SEP4_DEVICE_CODE_EVENTREACTOR_H

#include <io.h>

typedef struct preferences{
    uint8_t  lightPreference;
    uint8_t  buzzerPreference;
}preferences_t;

void toggleLights();
void toggleBuzzer();

#endif //SEP4_DEVICE_CODE_EVENTREACTOR_H
