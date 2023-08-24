

#define EPD_SPI &SPI0 // primary SPI



#include "Headers/Global.hpp"


#include "Headers/Audio.hpp"
#include "Headers/Core1.hpp"
#include "Headers/Datetime.hpp"
#include "Headers/Display.hpp"
#include "Headers/States.hpp"


unsigned long LAST_LIGHT_SWITCH;
bool LIGHT_VALUE;


void setup()
{
	Serial.begin(9600);
	Serial.println("Start");
	LAST_LIGHT_SWITCH = millis();
	LIGHT_VALUE = false;
	// Audio setup
	Global::Serial2.begin(9600);
	Serial1.begin(9600);
	Global::Audio::player.begin();
	Global::Audio::player.setVolume(10);

	// Display setup
	Serial.println("Start");
	Global::state = States::DISPLAY_TIME;
	Serial.println("Start");
	Global::display.begin();
}


void loop()
{
	Serial.println("Loop");
	// unsigned long current_timestamp = millis();
	// if(LAST_LIGHT_SWITCH + 1000 > current_timestamp)
	// {
	// 	LAST_LIGHT_SWITCH = current_timestamp;
	// 	LIGHT_VALUE = !LIGHT_VALUE;
	// 	digitalWrite(LED_BUILTIN, LIGHT_VALUE);
	// }

	// Global::datetime = current_timestamp;

	// I have elected to this switch-case as opposed to a function array to make the code safer
	switch(Global::state)
	{
		case States::DISPLAY_TIME:
		{
			Global::display.update();
			Global::state = States::SET_ALARM_MINUTE;
			// States::display_time();
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
