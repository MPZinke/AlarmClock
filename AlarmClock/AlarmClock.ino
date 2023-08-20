

#include "Headers/Global.hpp"


#include "Headers/Core1.hpp"
#include "Headers/Datetime.hpp"
#include "Headers/Display.hpp"
#include "Headers/States.hpp"


void setup()
{
	Global::state = Global::DISPLAY_TIME;
}


void loop()
{
	Global::datetime = millis();

	// I have elected to this switch-case as opposed to a function array to make the code safer
	switch(Global::state)
	{
		case Global::DISPLAY_TIME:
		{
			States::display_time();
		}
		case Global::SET_TIME_HOUR:
		{
			States::set_time_hour();
		}
		case Global::SET_TIME_MINUTE:
		{
			States::set_time_minute();
		}
		case Global::SET_ALARM_HOUR:
		{
			States::set_alarm_hour();
		}
		case Global::SET_ALARM_MINUTE:
		{
			States::set_alarm_minute();
		}
		case Global::PLAY_ALARM:
		{
			States::play_alarm();
		}
		case Global::STOP_ALARM:
		{
			States::stop_alarm();
		}
	}

	delay(100);
}
