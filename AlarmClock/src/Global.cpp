

#define EPD_SPI &SPI0 // primary SPI


#include "../Headers/Global.hpp"


#include "../Headers/Datetime.hpp"
#include "../Headers/Display.hpp"


#define EPD_SPI &SPI0 // primary SPI


namespace Global
{
	States::State state = States::DISPLAY_TIME;
	Datetime datetime(2023, 8, 17);
	Display display;
	UART Serial2(/* TX= */8, /* RX= */9, 0, 0);  // FROM: https://arduino.stackexchange.com/a/84737

	namespace Audio
	{
		DFPlayer player(Serial2);
	}
}
