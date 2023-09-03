

#include <FreeRTOS.h>
#include <task.h>


#include "../Headers/Global.hpp"


#include "../Headers/Button.hpp"
#include "../Headers/Core1.hpp"
#include "../Headers/Datetime.hpp"
#include "../Headers/Display.hpp"
#include "../Headers/Encoder.hpp"
#include "../Headers/StaticList.hpp"
#include "../Headers/Time.hpp"


namespace States
{
	State::State()
	: _state{NONE}
	{}


	State::State(::State state)
	: _state{state}, _start_time{millis()}
	{}


	unsigned long State::start_time()
	{
		return _start_time;
	}


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
			Encoder& encoder = Global::Inputs::encoder;
			if(encoder.has_changed())
			{
				adjust_audio();
			}

			// // If menu button has been pressed
			// if(Global::Inputs::buttons[Button::MENU].has_changed())
			// {
			// 	set_menu();
			// }
		}


		void adjust_audio()
		{
			using namespace Global::Audio;
			// Get change from encoder
			Global::Audio::volume += Global::Inputs::encoder.change();

			if(Global::Audio::volume < 0)
			{
				Global::Audio::volume = 0;
			}
			else if(30 < Global::Audio::volume)
			{
				Global::Audio::volume = 30;
			}

			Global::Audio::player.setVolume(Global::Audio::volume);
			if(Global::Audio::player.getStatus().state != DfMp3_StatusState_Playing)
			{
				Global::Audio::player.playFolderTrack(1, Audio::Tracks::DROP);
			}

			Global::Inputs::encoder.acknowledge();
			Global::Inputs::buttons.lambda(Button::static_acknowledge);
		}


		void set_menu()
		{
			Global::State::core0_state.push(State(States::MENU_ALARM));
			Global::State::core1_state.push(States::MENU_ALARM);

			Global::Inputs::encoder.acknowledge();
			Global::Inputs::buttons.lambda(Button::static_acknowledge);
		}
	}


	namespace Menu
	{
		void alarm()
		{}


		void time()
		{}


		void date()
		{}
	}


	namespace Alarm
	{
		uint8_t SELECTED_ALARM = 0;


		namespace Menu
		{
			void alarms()
			{}


			void new_alarm()
			{}


		}


		namespace Seletected
		{
			void delete_alarm()
			{}


			void edit()
			{}




			namespace Edit
			{
				void hour()
				{}


				void minute()
				{}


			}
		}


		namespace Alarm
		{
			void start_alarm()
			{
				Global::State::core0_state.push(State(States::PLAYING_ALARM));
				Global::State::core1_state.push(States::PLAYING_ALARM);
				Global::Audio::start = millis();

				Global::Audio::player.playFolderTrack(1, Audio::Tracks::ALARM);

				Global::Inputs::buttons.lambda(Button::static_acknowledge);
			}


			void playing_alarm()
			{
				if(millis() - Global::Audio::start >= 300000)
				{
					Global::State::core0_state.pop();
					Global::State::core0_state.push(State(States::STOP_ALARM));
					Global::State::core1_state.push(States::STOP_ALARM);
					return;
				}

				for(uint8_t x = 0; x < Global::Inputs::buttons.size(); x++)
				{
					if(Global::Inputs::buttons[x].has_changed() && Global::State::core0_state[-1] != States::STOP_ALARM)
					{
						Global::State::core0_state.pop();
						Global::State::core0_state.push(State(States::STOP_ALARM));
						Global::State::core1_state.push(States::STOP_ALARM);

						Global::Inputs::buttons.lambda(Button::static_acknowledge);

						return;
					}
				}
			}


			void stop_alarm()
			{
				Global::Audio::player.stop();
				Global::State::core0_state.pop();

				Global::Inputs::buttons.lambda(Button::static_acknowledge);
			}
		}
	}


	namespace Time
	{
		void hour()
		{}


		void minute()
		{}
	}


	namespace Date
	{
		void year()
		{
			// If 10 seconds have passed
			if(Global::Inputs::encoder.has_changed() && Global::Inputs::encoder.last_changed() >= 600000)
			{

			}
		}


		void month()
		{}


		void day()
		{}
	}
}
