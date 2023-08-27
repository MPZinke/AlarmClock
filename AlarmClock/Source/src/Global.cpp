


#include "../Headers/Global.hpp"


#include "../Headers/Datetime.hpp"
// #include "../Headers/Display.hpp"
#include "../Headers/StaticList.hpp"


namespace Global
{
	StaticList<3, States::State> core0_state(States::HOME);

	namespace Audio
	{
		SerialUART& serial = Serial1;
		DFPlayer player(Global::Audio::serial);
		uint8_t volume = 5;
	}

	namespace BlinkingLight
	{
		unsigned long last_switch;
		bool state;
	}

	namespace Time
	{
		StaticList<10, Alarm> alarms;
		Datetime datetime(2023, 8, 17);
	}

	// Display display(Global::Time::datetime);
}
