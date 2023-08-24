



#include "Headers/Global.hpp"


#include "Headers/Audio.hpp"
#include "Headers/Core1.hpp"
#include "Headers/Datetime.hpp"
#include "Headers/Display.hpp"
#include "Headers/States.hpp"


void setup()
{
	// Serial.begin(115200);
	Global::BlinkingLight::last_switch = millis();
	Global::BlinkingLight::state = false;
	// Audio setup
	Global::Hardware::Serial2.begin(9600);
	Global::Audio::player.begin();
	Global::Audio::player.setVolume(Global::Audio::volume);

	// Display setup
	// Global::Hardware::SPI1.begin();
	Global::state = States::DISPLAY_TIME;
	Global::display.begin();
}


void loop()
{
	unsigned long current_timestamp = millis();
	if(Global::BlinkingLight::last_switch + 1000 < current_timestamp)
	{
		Global::BlinkingLight::last_switch = current_timestamp;
		Global::BlinkingLight::state = !Global::BlinkingLight::state;
		digitalWrite(LED_BUILTIN, Global::BlinkingLight::state ? HIGH : LOW);
	}

	Global::datetime = current_timestamp;

	// I have elected to this switch-case as opposed to a function array to make the code safer
	switch(Global::state)
	{
		case States::DISPLAY_TIME:
		{
			States::display_time();
			break;
		}
		case States::SET_TIME_HOUR:
		{
			States::set_time_hour();
			break;
		}
		case States::SET_TIME_MINUTE:
		{
			States::set_time_minute();
			break;
		}
		case States::SET_ALARM_HOUR:
		{
			States::set_alarm_hour();
			break;
		}
		case States::SET_ALARM_MINUTE:
		{
			States::set_alarm_minute();
			break;
		}
		case States::PLAY_ALARM:
		{
			States::play_alarm();
			break;
		}
		case States::STOP_ALARM:
		{
			States::stop_alarm();
			break;
		}
	}

	delay(100);
}
