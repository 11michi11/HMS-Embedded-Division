#include <ATMEGA_FreeRTOS.h>
#include <stdio.h>
#include <stdlib.h>
#include <DataCollector.h>
#include <EventReactor.h>
#include <LoraHelper.h>
#include <interrupt.h>
#include <stdio_driver.h>

SemaphoreHandle_t semaphoreHandle;

int main() {
    stdioCreate(0);
    sei();
    sensor_data_t* sensorData=(sensor_data_t*)malloc(sizeof(sensor_data_t));
    preferences_t* preferences=(preferences_t*)malloc(sizeof(preferences_t));
    semaphoreHandle= xSemaphoreCreateMutex();
    initializeEventReactor(preferences);
    initializeDataCollector(sensorData,&semaphoreHandle);
    initializeHelper(sensorData,&semaphoreHandle,preferences);
    vTaskStartScheduler();
    return 0;
}