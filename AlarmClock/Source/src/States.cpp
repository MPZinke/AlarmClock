

#include <FreeRTOS.h>
#include <task.h>


#include "../Headers/Global.hpp"


#include "../Headers/Core1.hpp"
#include "../Headers/Datetime.hpp"
#include "../Headers/Display.hpp"
#include "../Headers/Time.hpp"


namespace States
{
	State::State(::State state)
	: _state{state}, _start_time{millis()}
	{}


	unsigned long State::start_time()
	{}


	State::operator uint8_t()
	{
		return _state;
	}


	namespace Home
	{
		void main()
		{
			unsigned long current_timestamp = millis();

			// Check if the encoder has been changed
			Encoder& encoder = Global::Hardware::encoder;
			if(encoder.has_changed() && current_timestamp - encoder.last_change() > 500)
			{
				adjust_audio();
			}

			// If menu button has been pressed
			Button& menu_button = Global::Hardware::buttons[Button::MENU];
			if(menu_button.has_changed())
			{
				set_menu();
			}
		}


		void adjust_audio()
		{
			// Get change from encoder
			Global::Audio::volume += Global::Hardware::encoder.change();

			if(Global::Audio::volume < 0)
			{
				Global::Audio::volume = 0;
			}
			else if(30 < Global::Audio::volume)
			{
				Global::Audio::volume = 30;
			}

			Global::Audio::player.setVolume(Global::Audio::volume);

			Global::Hardware::encoder.acknowledge();
			Global::Hardware::core0_state.lambda(Button::static_acknowledge);
		}


		void set_menu()
		{
			Global::States::core0_state.push(State(States::MENU));
			Global::States::core1_state.push(States::MENU);

			Global::Hardware::encoder.acknowledge();
			Global::Hardware::core0_state.lambda(Button::static_acknowledge);
		}
	}


	namespace Alarm
	{
		void set_hour()
		{}


		void set_minute()
		{}


		namespace Alarm
		{
			void start_alarm()
			{
				Global::State::core0_state.push(State(States::PLAYING_ALARM));
				Global::State::core1_state.push(States::PLAYING_ALARM);
				Global::Audio::start = millis();

				Global::Audio::player.playFolderTrack(1, Audio::Tracks::ALARM);

				Global::Hardware::buttons.lambda(Button::static_acknowledge);
			}


			void playing_alarm()
			{
				if(millis() - Global::Audio::start >= 300000)
				{
					Global::State::core0_state.pop();
					Global::State::core0_state.push(State(States::STOP_ALARM));
					Global::State::core1_state.push(States::STOP_ALARM);
				}

				for(uint8_t x = 0; x < Global::Hardware::buttons.size(); x++)
				{
					if(Global::Hardware::buttons.has_changed() && Global::State::core0_state[-1] != States::STOP_ALARM)
					{
						Global::State::core0_state.pop();
						Global::State::core0_state.push(State(States::STOP_ALARM));
						Global::State::core1_state.push(States::STOP_ALARM);

						Global::Hardware::buttons.lambda(Button::static_acknowledge);

						return;
					}
				}
			}


			void stop_alarm()
			{
				Global::Audio::player.stop();
				Global::State::core0_state.pop();

				Global::Hardware::buttons.lambda(Button::static_acknowledge);
			}
		}
	}


	namespace Time
	{
		void set_year()
		{
			// If 10 seconds have passed
			if(Global::Hardware::encoder.has_changed() && Global::Hardware::encoder.last_change() >= 600000)
		}


		void set_month()
		{}


		void set_day()
		{}


		void set_hour()
		{}


		void set_minute()
		{}
	}
}
