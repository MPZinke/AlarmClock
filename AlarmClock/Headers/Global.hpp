

#include <Adafruit_ThinkInk.h>  // For MbedSPI


#include "Audio.hpp"
#include "States.hpp"



class Alarm;
class Datetime;
class Display;


// ::Global::Audio::DFPlayer type set in Audio.hpp


namespace Global
{
	extern Alarm alarm;
	extern States::State state;
	extern Datetime datetime;
	extern Display display;

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
}
