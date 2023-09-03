
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
#include <pico/stdlib.h>
#include <hardware/pio.h>

#include <Arduino.h>
#include <DFMiniMp3.h>


#include "Headers/Global.hpp"


#include "Headers/Alarm.hpp"
#include "Headers/Audio.hpp"
#include "Headers/Core1.hpp"
#include "Headers/Datetime.hpp"
#include "Headers/Display.hpp"
#include "Headers/Encoder.hpp"
#include "Headers/StaticList.hpp"
#include "Headers/States.hpp"


void on_interrupt(uint gpio, uint32_t events)
{
	
}


void main_loop()
{
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
			Global::State::core0_state += States::START_ALARM;
		}

		Global::Inputs::encoder.update();
		// I have elected to this switch-case as opposed to an array of functions to make the code safer
		switch(Global::State::core0_state[-1])
		{
			case States::HOME:
			{
				States::Home::main();
				break;
			}

			// ———— MAIN MENU ———— //
			case States::Menu::ALARM:
			{
				States::Menu::alarm();
				break;
			}
			case States::Menu::TIME:
			{
				States::Menu::time();
				break;
			}
			case States::Menu::DATE:
			{
				States::Menu::date();
				break;
			}

			// ———— ALARM ———— //
			case States::Alarm::Menu::ALARMS:
			{
				States::Alarm::Menu::alarms();
				break;
			}
			case States::Alarm::Menu::NEW:
			{
				States::Alarm::Menu::new_alarm();
				break;
			}

			// ———— ALARM::SELECTED ———— //
			case States::Alarm::Seletected::EDIT:
			{
				States::Alarm::Seletected::edit();
				break;
			}
			case States::Alarm::Seletected::DELETE_ALARM:
			{
				States::Alarm::Seletected::delete_alarm();
				break;
			}
			case States::Alarm::Seletected::Edit::HOUR:
			{
				States::Alarm::Seletected::Edit::hour();
				break;
			}
			case States::Alarm::Seletected::Edit::MINUTE:
			{
				States::Alarm::Seletected::Edit::minute();
				break;
			}

			// ———— ALARM::ALARM ———— //
			case States::Alarm::Alarm::START_ALARM:
			{
				States::Alarm::Alarm::start_alarm();
				break;
			}
			case States::Alarm::Alarm::PLAYING_ALARM:
			{
				States::Alarm::Alarm::playing_alarm();
				break;
			}
			case States::Alarm::Alarm::STOP_ALARM:
			{
				States::Alarm::Alarm::stop_alarm();
				break;
			}
		}
	}
}


int main()
{
	Global::BlinkingLight::last_switch = millis();  // DEVELOPMENT
	Global::BlinkingLight::state = false;  // DEVELOPMENT

	// Initialize LED pin
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

	// Initialize chosen serial port
	stdio_init_all();

	Global::display.begin();

	Global::Audio::serial.begin(9600);
	Global::Audio::player.begin();
	Global::Audio::player.setVolume(Global::Audio::volume);

	Global::Audio::player.playFolderTrack(1, Audio::Tracks::START_UP);

	// FROM: https://forums.raspberrypi.com/viewtopic.php?t=338861
	// gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, Global::Inputs::encoder.update);
	// gpio_set_irq_enabled_with_callback(3, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, Global::Inputs::encoder.update);

	printf("All Initialized\r\n");
	xTaskCreate((TaskFunction_t)main_loop, "Clock", 256, NULL, 1, NULL);

	// FROM: https://github.com/ghubcoder/PicoFreertosBlink/blob/master/blink.c
	//  VIA: https://ghubcoder.github.io/posts/using-multiple-cores-pico-freertos/
	//  AND: https://embeddedcomputing.com/technology/open-source/linux-freertos-related/using-freertos-with-the-raspberry-pi-pico-part-4
	TaskHandle_t display_handle;
	UBaseType_t uxCoreAffinityMask;
	xTaskCreate((TaskFunction_t)Core1::main, "Display", 256, NULL, 1, &display_handle);
	uxCoreAffinityMask = 1 << 1;  // Force to run on core1. To force to run on core0: uxCoreAffinityMask = 1 << 0;
	vTaskCoreAffinitySet(display_handle, uxCoreAffinityMask);

	vTaskStartScheduler();

	loop{}
}

