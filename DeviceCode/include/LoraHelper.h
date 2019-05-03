
#include <DataRepository.h>
#include <EventReactor.h>

#ifndef SEP4_DEVICE_CODE_LORAHELPER_H
#define SEP4_DEVICE_CODE_LORAHELPER_H

void initialize_lora_helper(sensor_data_t *sensorData, SemaphoreHandle_t *semaphoreHandle, preferences_t *preferences);
void handle_message();
void parseMessage();

#endif //SEP4_DEVICE_CODE_LORAHELPER_H
