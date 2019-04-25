#include <ATMEGA_FreeRTOS.h>
#include <stdio.h>
#include <stdlib.h>
#include <DataCollector.h>
#include <EventReactor.h>
#include <LoraHelper.h>
#include <avr/interrupt.h>
#include <stdio_driver.h>
#include <ihal.h>
#include <lora_driver.h>
#include <util/delay.h>
#include <i_register_access.h>
#include <iled.h>
#include <tsl2591.h>
SemaphoreHandle_t semaphoreHandle;
sensor_data_t* sensorData;
preferences_t* preferences;
TimerHandle_t loraInitializerCountdown;

void loraInitialize();

int main() {
    stdioCreate(0);
    sei();
    sensorData=(sensor_data_t*)malloc(sizeof(sensor_data_t));
    preferences=(preferences_t*)malloc(sizeof(preferences_t));
    preferences->lightPreference=1;
    semaphoreHandle= xSemaphoreCreateMutex();
    initializeEventReactor(preferences);
    initializeDataCollector(sensorData,&semaphoreHandle);
//    initializeHelper(sensorData,&semaphoreHandle,preferences);
    vTaskStartScheduler();

    return 0;
}