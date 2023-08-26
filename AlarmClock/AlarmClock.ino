

#include <pico/multicore.h>


#include "Headers/Global.hpp"


#include "Headers/Audio.hpp"
#include "Headers/Core1.hpp"
#include "Headers/Datetime.hpp"
#include "Headers/Display.hpp"
#include "Headers/List.hpp"
#include "Headers/States.hpp"


void setup()
{
	Global::BlinkingLight::last_switch = millis();  // DEVELOPMENT
	Global::BlinkingLight::state = false;  // DEVELOPMENT

	// Core1 setup
	multicore_launch_core1(Core1::main);

	// Audio setup
	Global::Hardware::Serial2.begin(9600);
	Global::Audio::player.begin();
	Global::Audio::player.setVolume(Global::Audio::volume);

	// Display setup
	Global::display.begin();

	// Start initial steps
	Core1::update_display();
	Global::Audio::player.playFolderTrack(1, Audio::Tracks::START_UP);
}


void loop()
{
	unsigned long current_timestamp = millis();
	if(Global::BlinkingLight::last_switch + 1000 < current_timestamp)  // DEVELOPMENT
	{  // DEVELOPMENT
		Global::BlinkingLight::last_switch += 1000;  // DEVELOPMENT
		Global::BlinkingLight::state = !Global::BlinkingLight::state;  // DEVELOPMENT
		digitalWrite(LED_BUILTIN, Global::BlinkingLight::state ? HIGH : LOW);  // DEVELOPMENT
	}  // DEVELOPMENT

	Global::Time::datetime = current_timestamp;

	if((Time&)Global::Time::datetime == Global::Time::alarms[0])
	{
		Global::core0_state += States::START_ALARM;
	}

	// I have elected to this switch-case as opposed to an array of functions to make the code safer
	switch(Global::core0_state.peek())
	{
		case States::HOME:
		{
			States::display_time();
			break;
		}
		case States::SETTING_DATETIME_HOUR:
		{
			States::set_time_hour();
			break;
		}
		case States::SETTING_DATETIME_MINUTE:
		{
			States::set_time_minute();
			break;
		}
		case States::SETTING_ALARM_HOUR:
		{
			States::set_alarm_hour();
			break;
		}
		case States::SETTING_ALARM_MINUTE:
		{
			States::set_alarm_minute();
			break;
		}
		case States::START_ALARM:
		{
			States::start_alarm();
			break;
		}
		case States::PLAYING_ALARM:
		{
			States::playing_alarm();
			break;
		}
		case States::STOP_ALARM:
		{
			States::stop_alarm();
			break;
		}
	}

	delay(50);
}
