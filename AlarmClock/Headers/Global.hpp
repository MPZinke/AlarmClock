

#include "Audio.hpp"
#include "States.hpp"


#define EPD_SPI &SPI0 // primary SPI


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
	extern UART Serial2;

	namespace Audio
	{
		extern DFPlayer player;
		extern uint8_t volume;
	}
}
