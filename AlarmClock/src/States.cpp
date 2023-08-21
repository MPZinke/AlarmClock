

#pragma once


#include "pico/multicore.h"


#include "../Headers/Global.hpp"


#include "../Headers/Core1.hpp"
#include "../Headers/Datetime.hpp"
#include "../Headers/Display.hpp"
#include "../Headers/Time.hpp"


namespace States
{
	// Display time
	void display_time()
	{
		Time& display_time = (Time&)Global::display;
		if(display_time.hour() == Global::datetime.hour() && display_time.minute() == Global::datetime.minute()
		  && (Date&)Global::display == (Date&)Global::datetime
		)
		{
			return;
		}

		Global::display = (Time&)Global::datetime;
		multicore_launch_core1(Core1::update_display);
		// If alarm time
		//	Set alarm state
		// If user input for menu
		//	Set state to menu
	}


	void set_time_hour()
	{
		Global::datetime.hour(1);  // Testing
	}


	void set_time_minute()
	{
		Global::datetime.minute(1);  // Testing
	}


	void set_alarm_hour()
	{}


	void set_alarm_minute()
	{}


	void play_alarm()
	{
		// Check button press
		// If button pressed
			// Stop
	}


	void stop_alarm()
	{}
}
