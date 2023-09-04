


#include "../Headers/Global.hpp"


#include "../Headers/Alarm.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Core1.hpp"
#include "../Headers/Datetime.hpp"
#include "../Headers/Display.hpp"
#include "../Headers/Encoder.hpp"
#include "../Headers/StaticList.hpp"
#include "../Headers/Time.hpp"


namespace Global
{
	namespace State
	{
		StaticList<3, States::State> core0_state(States::State(States::Home::main));
		StaticList<3, States::State> core1_state(Core1::display_time);
	}

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
		StaticList<5, Button> buttons(Button(13), Button(12), Button(11), Button(10), Button(9));
		Encoder encoder(14, 15);
	}

	namespace Time
	{
		StaticList<10, Alarm> alarms;
		Datetime datetime(2023, 8, 17);
	}

	Display display(::Time((unsigned long)360));
}
