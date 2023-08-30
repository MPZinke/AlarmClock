

#include <FreeRTOS.h>
#include <task.h>


#include "../Headers/Global.hpp"


#include "../Headers/Core1.hpp"
#include "../Headers/Datetime.hpp"
#include "../Headers/Display.hpp"
#include "../Headers/Time.hpp"



namespace States
{
	namespace Home
	{
		void main()
		{
			// Update encoder && menu button

			// Check if the encoder has been changed
			if(Global::Hardware::encoder)
			{
				adjust_audio();
			}

			// If menu button has been pressed

		}


		void adjust_audio()
		{
			// Get change from encoder
		}
	}


	// Display time
	void display_time()
	{}


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
