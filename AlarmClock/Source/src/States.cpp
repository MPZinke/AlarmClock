

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

			// If menu button has been pressed
			if(Global::Inputs::buttons[Button::CENTER].has_changed())
			{
				set_menu();
			}
		}


		void adjust_audio()
		{
			using namespace Global::Audio;
			// Get change from encoder
			volume += Global::Inputs::encoder.change();

			if(volume < 0)
			{
				volume = 0;
			}
			else if(30 < volume)
			{
				volume = 30;
			}

			player.setVolume(volume);
			if(player.getStatus().state != DfMp3_StatusState_Playing)
			{
				player.playFolderTrack(1, Audio::Tracks::DROP);
			}

			Global::Inputs::encoder.acknowledge();
			Global::Inputs::buttons.lambda(Button::static_acknowledge);
		}


		void set_menu()
		{
			Global::State::core0_state.push(State(States::Menu::ALARM));
			Global::State::core1_state.push(States::Menu::ALARM);

			Global::Inputs::encoder.acknowledge();
			Global::Inputs::buttons.lambda(Button::static_acknowledge);
		}
	}


	namespace Menu
	{
		void alarm()
		{
			using namespace Global::Inputs;
			using namespace Global::State;

			if(buttons[Button::LEFT].has_changed())
			{
				core0_state.pop();
				core0_state.push(State(States::HOME));
				core1_state.push(State(States::HOME));

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state.pop();
				core0_state.push(State(States::Alarm::Menu::ALARMS));
				core1_state.push(State(States::Alarm::Menu::ALARMS));

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::DOWN].has_changed())
			{
				core0_state.pop();
				core0_state.push(State(States::Menu::TIME));
				core1_state.push(State(States::Menu::TIME));

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(millis() - core0_state[-1].start_time() >= 10000)
			{
				core0_state.pop();
				core0_state.push(State(States::HOME));
				core1_state.push(States::HOME);
				return;
			}
		}


		void time()
		{
			using namespace Global::Inputs;
			using namespace Global::State;

			if(buttons[Button::LEFT].has_changed())
			{
				core0_state.pop();
				core0_state.push(State(States::HOME));
				core1_state.push(State(States::HOME));

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::UP].has_changed())
			{
				core0_state.pop();
				core0_state.push(State(States::Menu::ALARM));
				core1_state.push(State(States::Menu::ALARM));

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state.pop();
				core0_state.push(State(States::Time::HOUR));
				core1_state.push(State(States::Time::HOUR));

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::DOWN].has_changed())
			{
				core0_state.pop();
				core0_state.push(State(States::Menu::DATE));
				core1_state.push(State(States::Menu::DATE));

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(millis() - core0_state[-1].start_time() >= 10000)
			{
				core0_state.pop();
				core0_state.push(State(States::HOME));
				core1_state.push(States::HOME);
				return;
			}
		}


		void date()
		{
			using namespace Global::Inputs;
			using namespace Global::State;

			if(buttons[Button::LEFT].has_changed())
			{
				core0_state.pop();
				core0_state.push(State(States::HOME));
				core1_state.push(State(States::HOME));

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::UP].has_changed())
			{
				core0_state.pop();
				core0_state.push(State(States::Menu::ALARM));
				core1_state.push(State(States::Menu::ALARM));

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state.pop();
				core0_state.push(State(States::Date::YEAR));
				core1_state.push(State(States::Date::YEAR));

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(millis() - core0_state[-1].start_time() >= 10000)
			{
				core0_state.pop();
				core0_state.push(State(States::HOME));
				core1_state.push(States::HOME);
				return;
			}
		}
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
				using namespace Global::Inputs;
				using namespace Global::State;

				if(millis() - Global::Audio::start >= 300000)
				{
					core0_state.pop();
					core0_state.push(State(States::Alarm::Alarm::STOP));
					core1_state.push(States::Alarm::Alarm::STOP);
					return;
				}

				for(uint8_t x = 0; x < Global::Inputs::buttons.size(); x++)
				{
					if(buttons[x].has_changed() && core0_state[-1] != States::Alarm::Alarm::STOP)
					{
						core0_state.pop();
						core0_state.push(State(States::Alarm::Alarm::STOP));
						core1_state.push(States::Alarm::Alarm::STOP);

						buttons.lambda(Button::static_acknowledge);

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
