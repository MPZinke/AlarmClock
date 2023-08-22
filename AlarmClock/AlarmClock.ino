

#include "Headers/Global.hpp"


#include "Headers/Audio.hpp"
#include "Headers/Core1.hpp"
#include "Headers/Datetime.hpp"
#include "Headers/Display.hpp"
#include "Headers/States.hpp"


void setup()
{
	// Audio setup
	Global::Audio::serial.begin(9600);
	Serial1.begin(9600);
	Global::Audio::player.begin();
	Global::Audio::player.setVolume(10);

	Global::state = States::PLAY_ALARM;
}


void loop()
{
	Global::datetime = millis();

	// I have elected to this switch-case as opposed to a function array to make the code safer
	switch(Global::state)
	{
		case States::DISPLAY_TIME:
		{
			States::display_time();
		}
		case States::SET_TIME_HOUR:
		{
			States::set_time_hour();
		}
		case States::SET_TIME_MINUTE:
		{
			States::set_time_minute();
		}
		case States::SET_ALARM_HOUR:
		{
			States::set_alarm_hour();
		}
		case States::SET_ALARM_MINUTE:
		{
			States::set_alarm_minute();
		}
		case States::PLAY_ALARM:
		{
			States::play_alarm();
		}
		case States::STOP_ALARM:
		{
			States::stop_alarm();
		}
	}

	delay(100);
}
