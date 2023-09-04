

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
	: _state{nullptr}
	{}


	State::State(void(*state)())
	: _state{state}, _start_time{millis()}
	{}

	unsigned long State::start_time()
	{
		return _start_time;
	}

	void State::start_time(unsigned long timestamp)
	{
		_start_time = timestamp;
	}

	void State::operator()()
	{
		_state();
	}

	(*State::operator void() const)()
	{
		assert(_state != nullptr);

		return _state;
	}

	State& State::operator=(State right)
	{
		_state = right._state;
		_start_time = right._start_time;

		return *this;
	}

	State& State::operator=(void(*right_state)())
	{
		_state = right_state;
		_start_time = millis();

		return *this;
	}

	bool State::operator==(State& right)
	{
		return _state == right._state;
	}

	bool State::operator==(void(*right_state)())
	{
		return _state == right_state;
	}

	bool State::operator!=(State& right)
	{
		return _state != right._state;
	}

	bool State::operator!=(void(*right_state)())
	{
		return _state != right_state;
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
			Global::State::core0_state[-1] = State(States::Menu::alarm);

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
				core0_state[-1] = States::Home::main;

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state[-1] = State(States::Alarm::Menu::alarms);

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::DOWN].has_changed())
			{
				core0_state[-1] = State(States::Menu::time);

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(millis() - core0_state[-1].start_time() >= 10000)
			{
				core0_state[-1] = States::Home::main;
			}
		}


		void time()
		{
			using namespace Global::Inputs;
			using namespace Global::State;

			if(buttons[Button::LEFT].has_changed())
			{
				core0_state[-1] = States::Home::main;

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::UP].has_changed())
			{
				core0_state[-1] = State(States::Menu::alarm);

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state[-1] = State(States::Time::hour);

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::DOWN].has_changed())
			{
				core0_state[-1] = State(States::Menu::date);

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(millis() - core0_state[-1].start_time() >= 10000)
			{
				core0_state[-1] = States::Home::main;
			}
		}


		void date()
		{
			using namespace Global::Inputs;
			using namespace Global::State;

			if(buttons[Button::LEFT].has_changed())
			{
				core0_state[-1] = States::Home::main;

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::UP].has_changed())
			{
				core0_state[-1] = State(States::Menu::alarm);

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state[-1] = State(States::Date::year);

				buttons.lambda(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(millis() - core0_state[-1].start_time() >= 10000)
			{
				core0_state[-1] = States::Home::main;
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
			void start()
			{
				Global::State::core0_state[-1] = States::Alarm::Alarm::playing;
				Global::Audio::start = millis();

				Global::Audio::player.playFolderTrack(1, Audio::Tracks::ALARM);

				Global::Inputs::buttons.lambda(Button::static_acknowledge);
			}


			void playing()
			{
				using namespace Global::Inputs;
				using namespace Global::State;

				if(millis() - Global::Audio::start >= 300000)
				{
					core0_state[-1] = States::Alarm::Alarm::stop;
					return;
				}

				// Check if any button pressed for dismissing it
				for(uint8_t x = 0; x < Global::Inputs::buttons.size(); x++)
				{
					if(buttons[x].has_changed() && core0_state[-1] != States::Alarm::Alarm::stop)
					{
						core0_state[-1] = States::Alarm::Alarm::stop;
						buttons.lambda(Button::static_acknowledge);
						return;
					}
				}
			}


			void stop()
			{
				Global::Audio::player.stop();
				Global::State::core0_state.pop();
				Global::State::core0_state[-1].start_time(millis());

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
