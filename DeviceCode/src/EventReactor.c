
#include "EventReactor.h"
#define BUZZER_PORT (PB7)
#define LIGHT_PORT (PB6)

static const int LIGHT_DURATION_S=(954/portTICK_PERIOD_MS)*10;
static const int BUZZER_DURATION_S=(954/portTICK_PERIOD_MS)*5;
TaskHandle_t eventReactorTask=NULL;
static preferences_t* privatePreferences;

void initializeEventReactor(preferences_t* preferences){
	initialize_servo_motor();
	privatePreferences=preferences;
    xTaskCreate(toggleLights,"LIGHT_TOGGLE",configMINIMAL_STACK_SIZE,NULL,2,&eventReactorTask);
    vTaskSuspend(eventReactorTask);
    DDRB |= _BV(LIGHT_PORT);
    DDRB |= _BV(BUZZER_PORT);
}

//TODO MERGE toggleLights with toggleBuzzer due to the fact that they both do the same thing, just take different out port
void toggleLights(){
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wmissing-noreturn"
	//FIXME IMPLEMENT ME
	printf("PRE-DELAY-TOGGLE \n");
	servo_move_to_90();
	printf("LIGHT TOGGLE 1\n");
	vTaskDelay((954/portTICK_PERIOD_MS)*10);
	servo_move_to_0();
	printf("LIGHT TOGGLE 2\n");
	#pragma clang diagnostic pop
}

void toggleBuzzer(){
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(1){
        //FIXME IMPLEMENT ME
        printf("PRE-DELAY-TOGGLE \n");
        if(privatePreferences->buzzerPreference){
            vTaskDelay(BUZZER_DURATION_S);
            vTaskSuspend(eventReactorTask);
        }
        else{
            vTaskSuspend(eventReactorTask);
        }
        printf("POST-DELAY-TOGGLE \n");
    }
#pragma clang diagnostic pop
}


