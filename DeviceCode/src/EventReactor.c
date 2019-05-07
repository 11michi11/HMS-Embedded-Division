
#include <EventReactor.h>
#include <servo.h>
#include "DataRepository.h"

static preferences_t* privatePreferences;

void initializeEventReactor(preferences_t* preferences){
	initialize_servo_motor();
	privatePreferences=preferences;
}


void toggleLights(){
	printf("TOGGLE_EXECUTE \n");
 	servo_move_to_90();
 	vTaskDelay(ONE_SECOND_SENSOR_TIMER);
 	servo_move_to_0();
}



