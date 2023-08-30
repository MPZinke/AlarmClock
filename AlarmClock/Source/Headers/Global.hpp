

#pragma once


#include "Alarm.hpp"
#include "Audio.hpp"
#include "Button.hpp"
#include "StaticList.hpp"
#include "States.hpp"


#define loop while(true)


class Datetime;
class Display;
class Encoder;


// ::Global::Audio::DFPlayer type set in Audio.hpp as to avoid circular importing


namespace Global
{
	namespace State
	{
		extern StaticList<3, States::State> core0_state;
		extern StaticList<3, States::State> core1_state;
	}

	namespace Audio
	{
		extern DFPlayer player;
		extern SerialUART& serial;
		extern unsigned long start;
		extern int16_t volume;
	}

	namespace BlinkingLight
	{
		extern unsigned long last_switch;
		extern bool state;
	}

	namespace Inputs
	{
		extern StaticList<5, Button> buttons;
		extern Encoder encoder;
	}

	namespace Time
	{
		extern StaticList<10, Alarm> alarms;
		extern Datetime datetime;
	}

	extern Display display;
}
