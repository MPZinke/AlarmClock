

#include "../Headers/Core1.hpp"


#include "../Headers/Global.hpp"


#include "../Headers/Datetime.hpp"
#include "../Headers/Display.hpp"
#include "../Headers/States.hpp"
#include "../Headers/StaticList.hpp"


namespace Core1
{
	void main()
	{
		loop
		{
			Global::State::core1_state[-1]();

			sleep_ms(50);
		}
	}


	void no_op()
	{}


	void display_time()
	{
		Time& display_time = (Time&)Global::display;

		if(display_time.hour() == Global::Time::datetime.hour()
		  && display_time.minute() == Global::Time::datetime.minute()
		  && (Date&)Global::display == (Date&)Global::Time::datetime
		)
		{
			return;
		}

		Global::display = (Date&)Global::Time::datetime;
		Global::display = (Time&)Global::Time::datetime;

		Global::display.update();
	}

	namespace Menu
	{
		void alarm()
		{
			Global::display.display_menu_alarm();
			Global::State::core1_state[-1] = no_op;
		}
	}
}
