
#include <EventReactor.h>
#include <servo.h>

static preferences_t* privatePreferences;

void initializeEventReactor(preferences_t* preferences){
	initialize_servo_motor();
	privatePreferences=preferences;
}


void toggleLights(){
	printf("TOGGLE_EXECUTE \n");
 	servo_move_to_90();
 	servo_move_to_0();
}



