
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


#include "Headers/Audio.hpp"
#include "Headers/Core1.hpp"
#include "Headers/Datetime.hpp"
#include "Headers/Display.hpp"
#include "Headers/StaticList.hpp"
#include "Headers/States.hpp"


void on_interrupt(uint gpio, uint32_t events)
{
	printf("It was activated\r\n");
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
			Global::core0_state += States::START_ALARM;
		}

		// I have elected to this switch-case as opposed to an array of functions to make the code safer
		switch(Global::core0_state[-1])
		{
			case States::HOME:
			{
				States::Home::main();
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
	gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, on_interrupt);
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

