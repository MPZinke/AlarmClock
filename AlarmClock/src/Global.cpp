


#include "../Headers/Global.hpp"


#include "../Headers/Datetime.hpp"
#include "../Headers/Display.hpp"
#include "../Headers/StaticList.hpp"


namespace Global
{
	StaticList<3, States::State> core0_state(States::HOME);

	namespace Audio
	{
		DFPlayer player(Hardware::Serial2);
		uint8_t volume = 5;
	}

	namespace BlinkingLight
	{
		unsigned long last_switch;
		bool state;
	}

	namespace Hardware
	{
		// FROM: https://github.com/arduino/ArduinoCore-mbed/blob/52caeac0926acbfb9a3f2b0fa3ba1c9996f103ec/libraries/SPI/SPI.h#L31C
		MbedSPI SPI1(/* miso= */0,/* mosi= */3,/* sck= */2);
		UART Serial2(/* TX= */8, /* RX= */9, 0, 0);  // FROM: https://arduino.stackexchange.com/a/84737
	}

	namespace Time
	{
		StaticList<10, Alarm> alarms;
		Datetime datetime(2023, 8, 17);
	}

	Display display(Global::Time::datetime);
}
