

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

	// Audio
	extern DFRobotDFPlayerMini player;
}
