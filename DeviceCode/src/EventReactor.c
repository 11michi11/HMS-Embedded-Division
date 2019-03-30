//
// Created by PC on 3/29/2019.
//

#include "EventReactor.h"
#define BUZZER_PORT (PB0)
#define LIGHT_PORT (PB1)

static const int LIGHT_DURATION_MS=(954/portTICK_PERIOD_MS)*30;
static const int BUZZER_DURATION_MS=100;
TaskHandle_t eventReactorTask=NULL;


void toggleLights(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(1){
        //FIXME IMPLEMENT ME
            printf("PRE-DELAY-TOGGLE \n");
            vTaskDelay(LIGHT_DURATION_MS);
            printf("POST-DELAY-TOGGLE \n");
            vTaskSuspend(eventReactorTask);
          }
#pragma clang diagnostic pop
}


void toggleBuzzer(){

}

