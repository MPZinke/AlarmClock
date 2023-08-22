

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
	extern UART Serial2;
	extern uint8_t volume;

	namespace Audio
	{
		extern DFPlayer player;
		extern UART& serial;
	}
}
