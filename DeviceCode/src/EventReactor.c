
#include "EventReactor.h"
#define BUZZER_PORT (PB0)
#define LIGHT_PORT (PB1)

static const int LIGHT_DURATION_S=(954/portTICK_PERIOD_MS)*30;
static const int BUZZER_DURATION_S=(954/portTICK_PERIOD_MS)*5;
TaskHandle_t eventReactorTask=NULL;
static preferences_t* privatePreferences;

void initializeEventReactor(preferences_t* preferences){
    privatePreferences=preferences;
    xTaskCreate(toggleLights,"LIGHT_TOGGLE",configMINIMAL_STACK_SIZE,NULL,2,&eventReactorTask);
    vTaskSuspend(eventReactorTask);
}

//TODO MERGE toggleLights with toggleBuzzer due to the fact that they both do the same thing, just take different out port
void toggleLights(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(1){
        //FIXME IMPLEMENT ME
            printf("PRE-DELAY-TOGGLE \n");
            if(privatePreferences->lightPreference){
                vTaskDelay(LIGHT_DURATION_S);
                vTaskSuspend(eventReactorTask);
            } else vTaskSuspend(eventReactorTask);
        printf("POST-DELAY-TOGGLE \n");
          }
#pragma clang diagnostic pop
}

void toggleBuzzer(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(1){
        //FIXME IMPLEMENT ME
        printf("PRE-DELAY-TOGGLE \n");
        printf("POST-DELAY-TOGGLE \n");
        if(privatePreferences->buzzerPreference){
            vTaskDelay(BUZZER_DURATION_S);
            vTaskSuspend(eventReactorTask);
        }
        else{
            vTaskSuspend(eventReactorTask);
        }
    }
#pragma clang diagnostic pop
}

