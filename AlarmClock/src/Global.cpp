

#include "../Headers/Global.hpp"


#include "../Headers/Datetime.hpp"
#include "../Headers/Display.hpp"


namespace Global
{
	States::State state = States::DISPLAY_TIME;
	Datetime datetime(2023, 8, 17);
	Display display;

	DFRobotDFPlayerMini player;
}
