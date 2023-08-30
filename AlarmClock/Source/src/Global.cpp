


#include "../Headers/Global.hpp"


#include "../Headers/Datetime.hpp"
#include "../Headers/Display.hpp"
#include "../Headers/StaticList.hpp"
#include "../Headers/Time.hpp"


namespace Global
{
	StaticList<3, States::State> core0_state(States::HOME);
	StaticList<3, States::State> core1_state(States::HOME);

	namespace Audio
	{
		SerialUART& serial = Serial1;
		DFPlayer player(Global::Audio::serial);
		unsigned long start;
		int16_t volume = 5;
	}

	namespace BlinkingLight
	{
		unsigned long last_switch;
		bool state;
	}

	namespace Inputs
	{
		StaticList<5, Button> buttons(Button(0), Button(1), Button(2), Button(3), Button(4));
		Encoder encoder(2, 3);
	}

	namespace Time
	{
		StaticList<10, Alarm> alarms;
		Datetime datetime(2023, 8, 17);
	}

	Display display(::Time((unsigned long)360));
}
