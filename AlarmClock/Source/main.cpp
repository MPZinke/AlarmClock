
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
			Global::State::core0_state += States::Alarm::Alarm::start;
		}

		Global::State::core0_state[-1]();
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
	gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, true, Global::Inputs::encoder.update);
	gpio_set_irq_enabled_with_callback(3, GPIO_IRQ_EDGE_RISE|GPIO_IRQ_EDGE_FALL, true, Global::Inputs::encoder.update);

	printf("All Initialized\r\n");
	xTaskCreate((TaskFunction_t)main_loop, "Clock", 256, NULL, 1, NULL);
	// Pin the second task to the seconds core.
	// FROM: https://github.com/ghubcoder/PicoFreertosBlink/blob/master/blink.c
	//  VIA: https://ghubcoder.github.io/posts/using-multiple-cores-pico-freertos/
	//  AND: https://embeddedcomputing.com/technology/open-source/linux-freertos-related/using-freertos-with-the-raspberry-pi-pico-part-4
	TaskHandle_t display_handle;
	UBaseType_t uxCoreAffinityMask;
	xTaskCreate((TaskFunction_t)Core1::main, "Display", 256, NULL, 1, &display_handle);
	// Force to run on core1. To force to run on core0: uxCoreAffinityMask = 1 << 0;
	vTaskCoreAffinitySet(display_handle, (UBaseType_t)(/* uxCoreAffinityMask = */1 << 1));

	vTaskStartScheduler();

	loop{}
}

