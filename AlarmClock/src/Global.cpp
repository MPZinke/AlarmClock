

#include "../Headers/Global.hpp"


#include "../Headers/Datetime.hpp"
#include "../Headers/Display.hpp"


namespace Global
{
	States::State state = States::DISPLAY_TIME;
	Datetime datetime(2023, 8, 17);
	Display display;
	UART Serial2(12, 13, 0, 0);  // FROM: https://arduino.stackexchange.com/a/84737

	namespace Audio
	{
		UART& serial = Serial2;
		DFPlayer player(serial);
	}
}
