//
// Created by PC on 3/29/2019.
//

#include "EventReactor.h"
#define BUZZER_PORT (PB0)
#define LIGHT_PORT (PB1)

static const int LIGHT_DURATION_MS=30000;
static const int BUZZER_DURATION_MS=100;
TaskHandle_t eventReactorTask=NULL;


void toggleLights(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(1){
        //FIXME IMPLEMENT ME
            printf("PRE-DELAY-TOGGLE \n");
            vTaskDelay(pdMS_TO_TICKS(30));
            printf("POST-DELAY-TOGGLE \n");
            vTaskSuspend(eventReactorTask);
            vTaskDelay(0);
          }
#pragma clang diagnostic pop
}


void toggleBuzzer(){

}

