
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
#include "SerialUART.h"

#include <Arduino.h>
#include <DFMiniMp3.h>

#include <stdio.h>
#include "pico/stdlib.h"
#include "SPI.h"


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


DFPlayer player(Serial1);


int main() {

    const uint led_pin = 25;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize chosen serial port
    stdio_init_all();

    Serial1.begin(9600);
	player.begin();
	player.setVolume(5);
	player.playFolderTrack(1,1);

    // Loop forever
    while (true) {

        // Blink LED
        printf("Blinking!\r\n");
        gpio_put(led_pin, true);
        sleep_ms(1000);
        gpio_put(led_pin, false);
        sleep_ms(1000);
    }
}
