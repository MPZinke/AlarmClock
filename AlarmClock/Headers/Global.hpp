

#include "DFRobotDFPlayerMini.h"


#include "States.hpp"


class Alarm;
class Datetime;
class Display;


namespace Global
{
	extern Alarm alarm;
	extern States::State state;
	extern Datetime datetime;
	extern Display display;
	extern UART Serial2;

	namespace Audio
	{
		extern DFRobotDFPlayerMini player;
		extern UART& serial;
	}
}
