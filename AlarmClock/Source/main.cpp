
/***********************************************************************************************************************
*                                                                                                                      *
*   created by: MPZinke                                                                                                *
*   on 2023.08.26                                                                                                      *
*                                                                                                                      *
*   DESCRIPTION: TEMPLATE                                                                                              *
*   BUGS:                                                                                                              *
*   FUTURE:                                                                                                            *
*                                                                                                                      *
***********************************************************************************************************************/


#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"
// #include "SerialUART.h"

#include <Arduino.h>
#include <DFMiniMp3.h>


#include "Headers/Global.hpp"


#include "Headers/Audio.hpp"
#include "Headers/Core1.hpp"
#include "Headers/Datetime.hpp"
// #include "Headers/Display.hpp"
#include "Headers/StaticList.hpp"
#include "Headers/States.hpp"


#define loop while(true)


class Notifier;


typedef DFMiniMp3<HardwareSerial, Notifier> DFPlayer;


class Notifier
{
	public:
		static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action){}
		static void OnError([[maybe_unused]] DFPlayer& mp3, uint16_t errorCode){}
		static void OnPlayFinished([[maybe_unused]] DFPlayer& mp3, [[maybe_unused]] DfMp3_PlaySources source,
			uint16_t track
		){}
		static void OnPlaySourceOnline([[maybe_unused]] DFPlayer& mp3, DfMp3_PlaySources source){}
		static void OnPlaySourceInserted([[maybe_unused]] DFPlayer& mp3, DfMp3_PlaySources source){}
		static void OnPlaySourceRemoved([[maybe_unused]] DFPlayer& mp3, DfMp3_PlaySources source){}
};


int main()
{
	Global::BlinkingLight::last_switch = millis();  // DEVELOPMENT
	Global::BlinkingLight::state = false;  // DEVELOPMENT

	// Initialize LED pin
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

	// Initialize chosen serial port
	stdio_init_all();

	Global::Audio::serial.begin(9600);
	Global::Audio::player.begin();
	Global::Audio::player.setVolume(Global::Audio::volume);
	Global::Audio::player.playFolderTrack(1, Audio::Tracks::START_UP);

	loop
	{
		unsigned long current_timestamp = millis();
		if(Global::BlinkingLight::last_switch + 1000 < current_timestamp)  // DEVELOPMENT
		{  // DEVELOPMENT
			for(uint8_t limit = 0xFF; Global::BlinkingLight::last_switch + 1000 < current_timestamp && limit > 0; limit--)  // DEVELOPMENT
			{  // DEVELOPMENT
				Global::BlinkingLight::last_switch += 1000;  // DEVELOPMENT
			}  // DEVELOPMENT
			Global::BlinkingLight::state = !Global::BlinkingLight::state;  // DEVELOPMENT
			gpio_put(PICO_DEFAULT_LED_PIN, Global::BlinkingLight::state);  // DEVELOPMENT
		}  // DEVELOPMENT

		Global::Time::datetime = current_timestamp;

		if(Global::Time::alarms.size() && (Time&)Global::Time::datetime == Global::Time::alarms[0])
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

		sleep_ms(50);
	}
}
