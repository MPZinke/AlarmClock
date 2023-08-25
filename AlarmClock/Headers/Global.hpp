

#pragma once


#include <Adafruit_ThinkInk.h>  // For MbedSPI


#include "Audio.hpp"
#include "States.hpp"


class AlarmSet;
class Datetime;
class Display;


// ::Global::Audio::DFPlayer type set in Audio.hpp


namespace Global
{
	extern Display display;
	extern States::State state;

	namespace Audio
	{
		extern DFPlayer player;
		extern uint8_t volume;
	}

	namespace BlinkingLight
	{
		extern unsigned long last_switch;
		extern bool state;
	}

	namespace Hardware
	{
		extern MbedSPI SPI1;
		extern UART Serial2;
	}

	namespace Time
	{
		extern AlarmSet alarms;
		extern Datetime datetime;
	}
}
