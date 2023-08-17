

#include "Headers/Global.hpp"
#include "Headers/Datetime.hpp"


void display_time();
void set_time_hour();
void set_time_minute();
void set_alarm_hour();
void set_alarm_minute();
void play_alarm();
void stop_alarm();


void setup()
{
	Global::state = Global::DISPLAY_TIME;
}


void loop()
{
	// I have elected to this switch-case as opposed to a function array to make the code safer
	switch(Global::state)
	{
		case Global::DISPLAY_TIME:
		{
			display_time();
		}
		case Global::SET_TIME_HOUR:
		{
			set_time_hour();
		}
		case Global::SET_TIME_MINUTE:
		{
			set_time_minute();
		}
		case Global::SET_ALARM_HOUR:
		{
			set_alarm_hour();
		}
		case Global::SET_ALARM_MINUTE:
		{
			set_alarm_minute();
		}
		case Global::PLAY_ALARM:
		{
			play_alarm();
		}
		case Global::STOP_ALARM:
		{
			stop_alarm();
		}
	}

	delay(100);
}


// Display time
void display_time()
{
	// If minute has incremented
	// if(Global::datetime)
	{
		// Update screen thread
	}

	// If alarm time
	//	Set alarm state
	// If user input for menu
	//	Set state to menu
}
