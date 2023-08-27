

#pragma once


#include "pico/multicore.h"


#include "../Headers/Global.hpp"


#include "../Headers/Core1.hpp"
#include "../Headers/Datetime.hpp"
// #include "../Headers/Display.hpp"
#include "../Headers/Time.hpp"



namespace States
{
	// Display time
	void display_time()
	{
		// Time& display_time = (Time&)Global::display;

		// if(display_time.hour() == Global::Time::datetime.hour()
		//   && display_time.minute() == Global::Time::datetime.minute()
		//   && (Date&)Global::display == (Date&)Global::Time::datetime
		// )
		// {
		// 	return;
		// }

		// Global::display = (Date&)Global::Time::datetime;
		// Global::display = (Time&)Global::Time::datetime;
		// xTaskCreatePinnedToCore((TaskFunction_t)Core1::update_display, "Update Display", 10000, NULL, 2, NULL, 1);
	}


	void set_time_hour()
	{
		Global::Time::datetime.hour(1);  // Testing
	}


	void set_time_minute()
	{
		Global::Time::datetime.minute(1);  // Testing
	}


	void set_alarm_hour()
	{}


	void set_alarm_minute()
	{}


	void start_alarm()
	{
		Global::Audio::player.playFolderTrack(1, Audio::Tracks::ALARM);

		Global::core0_state.pop();
		Global::core0_state += STOP_ALARM;
	}


	void playing_alarm()
	{

		// Check button press
		// If button pressed
			// Stop
	}


	void stop_alarm()
	{}
}
