

#include <FreeRTOS.h>
#include <task.h>


#include "../Headers/Global.hpp"


#include "../Headers/Alarm.hpp"
#include "../Headers/Button.hpp"
#include "../Headers/Core1.hpp"
#include "../Headers/Date.hpp"
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
	: _state{state}, _last_updated{millis()}
	{}

	unsigned long State::last_updated()
	{
		return _last_updated;
	}

	void State::last_updated(unsigned long timestamp)
	{
		_last_updated = timestamp;
	}

	void State::operator()()
	{
		assert(_state != nullptr);

		_state();
	}

	State& State::operator=(State right)
	{
		_state = right._state;
		_last_updated = right._last_updated;

		return *this;
	}

	State& State::operator=(void(*right_state)())
	{
		_state = right_state;
		_last_updated = millis();

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
			using namespace Global::Inputs;

			unsigned long current_timestamp = millis();

			// Check if the encoder has been changed
			if(encoder.has_changed())
			{
				adjust_audio();
			}

			// If menu button has been pressed
			if(buttons[Button::CENTER].has_changed())
			{
				Global::State::core0_state.push(States::Menu::alarm);
				Global::State::core1_state.push(Core1::Menu::alarm);
			}

			Global::Inputs::encoder.acknowledge();
			Global::Inputs::buttons(Button::static_acknowledge);
		}


		void adjust_audio()
		{
			using namespace Global::Audio;
			using namespace Global::Inputs;

			// Get change from encoder
			volume += encoder.change();

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
				core0_state.pop();  // Home | Menu[Alarm]
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state.push(States::Alarm::Menu::alarms);
				Alarm::SELECTED_ALARM = 0;
			}

			else if(buttons[Button::DOWN].has_changed())
			{
				core0_state[-1] = States::Menu::time;
			}

			else if(millis() - core0_state[-1].last_updated() >= 10000)
			{
				core0_state.pop();  // Home | Menu[Alarm]
			}

			buttons(Button::static_acknowledge);
			encoder.acknowledge();
		}


		void time()
		{
			using namespace Global::Inputs;
			using namespace Global::State;

			if(buttons[Button::LEFT].has_changed())
			{
				core0_state.pop();
				core0_state[-1].last_updated(millis());
			}

			else if(buttons[Button::UP].has_changed())
			{
				core0_state[-1] = States::Menu::alarm;
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state.push(States::Time::hour);
			}

			else if(buttons[Button::DOWN].has_changed())
			{
				core0_state[-1] = States::Menu::date;
			}

			else if(millis() - core0_state[-1].last_updated() >= 10000)
			{
				core0_state.pop();  // Home | Menu[Time]
			}
		}


		void date()
		{
			using namespace Global::Inputs;
			using namespace Global::State;

			if(buttons[Button::LEFT].has_changed())
			{
				core0_state.pop();
				core0_state[-1].last_updated(millis());
			}

			else if(buttons[Button::UP].has_changed())
			{
				core0_state[-1] = States::Menu::alarm;
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state.push(States::Date::year);
			}

			else if(millis() - core0_state[-1].last_updated() >= 10000)
			{
				core0_state.pop();  // Home | Menu[Date]
			}

			buttons(Button::static_acknowledge);
			encoder.acknowledge();
		}
	}


	namespace Alarm
	{
		uint8_t SELECTED_ALARM = 0;


		namespace Menu
		{
			void alarms()
			{
				using namespace Global::Inputs;
				using namespace Global::State;

				if(buttons[Button::LEFT].has_changed())
				{
					core0_state.pop();  // Home | Menu[Alarm] | Alarm Menu[Alarms]
					core0_state[-1].last_updated(millis());
				}

				else if(buttons[Button::UP].has_changed())
				{
					if(States::Alarm::SELECTED_ALARM != 0)
					{
						States::Alarm::SELECTED_ALARM -= 1;
					}
				}

				else if(buttons[Button::CENTER].has_changed())
				{
					core0_state.push(States::Alarm::Selected::edit);
				}

				else if(buttons[Button::DOWN].has_changed())
				{
					States::Alarm::SELECTED_ALARM += 1;
					if(States::Alarm::SELECTED_ALARM == Global::Time::alarms.size()-1)
					{
						core0_state[-1] = States::Alarm::Menu::new_alarm;
					}
				}

				else if(millis() - core0_state[-1].last_updated() >= 10000)
				{
					core0_state.pop(2);  // Home | Menu[Alarm] | Alarm Menu[Alarms]
				}

				buttons(Button::static_acknowledge);
				encoder.acknowledge();
			}


			void new_alarm()
			{
				using namespace Global::Inputs;
				using namespace Global::State;

				if(buttons[Button::LEFT].has_changed())
				{
					core0_state.pop();  // Home | Menu[Alarm] | Alarm Menu[New]
					core0_state[-1].last_updated(millis());
				}

				else if(buttons[Button::UP].has_changed() && Global::Time::alarms.size() != 0)
				{
					States::Alarm::SELECTED_ALARM -= 1;
					core0_state[-1] = States::Alarm::Menu::alarms;
				}

				else if(buttons[Button::CENTER].has_changed())
				{
					core0_state.push(States::Alarm::Selected::edit);
				}

				else if(millis() - core0_state[-1].last_updated() >= 10000)
				{
					core0_state.pop(2);  // Home | Menu[Alarm] | Alarm Menu[New]
				}

				buttons(Button::static_acknowledge);
				encoder.acknowledge();
			}
		}


		namespace Selected
		{
			void edit()
			{
				using namespace Global::Inputs;
				using namespace Global::State;

				if(buttons[Button::LEFT].has_changed())
				{
					core0_state.pop();  // Home | Menu[Alarm] | Alarm Menu[New] | Selected[Edit]
					core0_state[-1].last_updated(millis());
				}

				else if(buttons[Button::CENTER].has_changed())
				{
					core0_state.push(States::Alarm::Selected::Edit::hour);
					Global::Time::alarms.push(::Alarm(8, 0));
				}

				else if(buttons[Button::DOWN].has_changed())
				{
					core0_state[-1] = States::Alarm::Selected::delete_alarm;
				}

				else if(millis() - core0_state[-1].last_updated() >= 10000)
				{
					core0_state.pop(3);  // Home | Menu[Alarm] | Alarm Menu[New] | Selected[Edit]
				}

				buttons(Button::static_acknowledge);
				encoder.acknowledge();
			}


			void delete_alarm()
			{
				using namespace Global::Inputs;
				using namespace Global::State;

				if(buttons[Button::LEFT].has_changed())
				{
					core0_state.pop();  // Home | Menu[Alarm] | Alarm Menu[New] | Selected[Delete]
					core0_state[-1].last_updated(millis());
				}

				else if(buttons[Button::UP].has_changed())
				{
					core0_state[-1] = States::Alarm::Selected::edit;
				}

				else if(buttons[Button::CENTER].has_changed())
				{
					Global::Time::alarms.pop();
					core0_state.pop(3);  // Home | Menu[Alarm] | Alarm Menu[New] | Selected[Delete]
				}

				else if(millis() - core0_state[-1].last_updated() >= 10000)
				{
					core0_state.pop(3);  // Home | Menu[Alarm] | Alarm Menu[New] | Selected[Delete]
				}

				buttons(Button::static_acknowledge);
				encoder.acknowledge();
			}


			namespace Edit
			{
				void hour()
				{
					using namespace Global::Inputs;
					using namespace Global::State;

					if(encoder.has_changed())
					{
						if(encoder.last_changed() >= 500)
						{
							int16_t hour = (int16_t)Global::Time::alarms[States::Alarm::SELECTED_ALARM].hour();
							hour += encoder.change();
							if(23 < hour)
							{
								hour = 23;
							}
							if(hour < 0)
							{
								hour = 0;
							}
							Global::Time::alarms[States::Alarm::SELECTED_ALARM].hour(hour);

							buttons(Button::static_acknowledge);
							encoder.acknowledge();
							core0_state[-1].last_updated(millis());
						}
					}

					else if(buttons[Button::CENTER].has_changed())
					{
						core0_state[-1] = States::Alarm::Selected::Edit::minute;

						buttons(Button::static_acknowledge);
						encoder.acknowledge();
					}

					else if(millis() - core0_state[-1].last_updated() >= 10000)
					{
						core0_state.pop(4);  // Home | Menu[Alarm] | Alarm Menu[New] | Selected[Edit] | Edit[Hour]

						buttons(Button::static_acknowledge);
						encoder.acknowledge();	
					}
				}


				void minute()
				{
					using namespace Global::Inputs;
					using namespace Global::State;

					if(encoder.has_changed())
					{
						if(encoder.last_changed() >= 500)
						{
							int16_t minute = (int16_t)Global::Time::alarms[States::Alarm::SELECTED_ALARM].minute();
							minute += encoder.change();
							if(59 < minute)
							{
								minute = 59;
							}
							if(minute < 0)
							{
								minute = 0;
							}
							Global::Time::alarms[States::Alarm::SELECTED_ALARM].minute(minute);

							buttons(Button::static_acknowledge);
							encoder.acknowledge();
							core0_state[-1].last_updated(millis());
						}
					}

					else if(buttons[Button::CENTER].has_changed())
					{
						core0_state.pop(4);  // Home | Menu[Alarm] | Alarm Menu[New] | Selected[Edit] | Edit[Minute]
						
						buttons(Button::static_acknowledge);
						encoder.acknowledge();
					}

					else if(millis() - core0_state[-1].last_updated() >= 10000)
					{
						core0_state.pop(4);  // Home | Menu[Alarm] | Alarm Menu[New] | Selected[Edit] | Edit[Minute]

						buttons(Button::static_acknowledge);
						encoder.acknowledge();	
					}
				}
			}
		}


		namespace Alarm
		{
			void start()
			{
				Global::State::core0_state[-1] = States::Alarm::Alarm::playing;

				Global::Audio::player.playFolderTrack(1, Audio::Tracks::ALARM);

				Global::Inputs::buttons(Button::static_acknowledge);
				Global::Inputs::encoder.acknowledge();
			}


			void playing()
			{
				using namespace Global::Inputs;
				using namespace Global::State;

				if(millis() - core0_state[-1].last_updated() >= 300000)
				{
					States::Alarm::Alarm::stop();
					return;
				}

				// Check if any button pressed for dismissing it
				for(uint8_t x = 0; x < Global::Inputs::buttons.size(); x++)
				{
					if(buttons[x].has_changed() && core0_state[-1] != States::Alarm::Alarm::stop)
					{
						States::Alarm::Alarm::stop();
						buttons(Button::static_acknowledge);
						return;
					}
				}
			}


			void stop()
			{
				Global::Audio::player.stop();
				Global::State::core0_state.pop();
				Global::State::core0_state[-1].last_updated(millis());

				Global::Inputs::buttons(Button::static_acknowledge);
			}
		}
	}


	namespace Time
	{
		void hour()
		{
			using namespace Global::Inputs;
			using namespace Global::State;

			if(encoder.has_changed())
			{
				if(encoder.last_changed() >= 500)
				{
					int16_t hour = (int16_t)Global::Time::datetime.hour() + encoder.change();
					if(23 < hour)
					{
						hour = 23;
					}
					if(hour < 0)
					{
						hour = 0;
					}
					Global::Time::datetime.hour(hour);

					buttons(Button::static_acknowledge);
					encoder.acknowledge();
					core0_state[-1].last_updated(millis());
				}
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state[-1] = States::Time::minute;

				buttons(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(millis() - core0_state[-1].last_updated() >= 10000)
			{
				core0_state.pop(2);  // Home | Menu[Time] | Hour

				buttons(Button::static_acknowledge);
				encoder.acknowledge();	
			}
		}


		void minute()
		{
			using namespace Global::Inputs;
			using namespace Global::State;

			if(encoder.has_changed())
			{
				if(encoder.last_changed() >= 500)
				{
					int16_t minute = (int16_t)Global::Time::datetime.minute() + encoder.change();
					if(23 < minute)
					{
						minute = 23;
					}
					if(minute < 0)
					{
						minute = 0;
					}
					Global::Time::datetime.minute(minute);

					buttons(Button::static_acknowledge);
					encoder.acknowledge();
					core0_state[-1].last_updated(millis());
				}
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state[-1] = States::Alarm::Selected::Edit::minute;

				buttons(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(millis() - core0_state[-1].last_updated() >= 10000)
			{
				core0_state.pop(4);  // Home | Menu[Alarm] | Alarm Menu[New] | Selected[Edit] | Edit[Hour]

				buttons(Button::static_acknowledge);
				encoder.acknowledge();	
			}
		}
	}


	namespace Date
	{
		void year()
		{
			using namespace Global::Inputs;
			using namespace Global::State;

			if(encoder.has_changed())
			{
				if(encoder.last_changed() >= 500)
				{
					int16_t year = (int16_t)Global::Time::datetime.year() + encoder.change();
					if(23 < year)
					{
						year = 23;
					}
					if(year < 0)
					{
						year = 0;
					}
					Global::Time::datetime.year(year);

					buttons(Button::static_acknowledge);
					encoder.acknowledge();
					core0_state[-1].last_updated(millis());
				}
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state[-1] = States::Date::month;

				buttons(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(millis() - core0_state[-1].last_updated() >= 10000)
			{
				core0_state.pop(2);  // Home | Menu[Date] | Date[Year]

				buttons(Button::static_acknowledge);
				encoder.acknowledge();	
			}
		}


		void month()
		{
			using namespace Global::Inputs;
			using namespace Global::State;

			if(encoder.has_changed())
			{
				if(encoder.last_changed() >= 500)
				{
					int16_t month = (int16_t)Global::Time::datetime.month() + encoder.change();
					if(12 < month)
					{
						month = 12;
					}
					if(month < 1)
					{
						month = 1;
					}
					Global::Time::datetime.month(month);

					buttons(Button::static_acknowledge);
					encoder.acknowledge();
					core0_state[-1].last_updated(millis());
				}
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state[-1] = States::Date::day;

				buttons(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(millis() - core0_state[-1].last_updated() >= 10000)
			{
				core0_state.pop(2);  // Home | Menu[Date] | Date[Month]

				buttons(Button::static_acknowledge);
				encoder.acknowledge();	
			}
		}


		void day()
		{
			using namespace Global::Inputs;
			using namespace Global::State;

			if(encoder.has_changed())
			{
				if(encoder.last_changed() >= 500)
				{
					int16_t day = (int16_t)Global::Time::datetime.day() + encoder.change();
					uint8_t month = Global::Time::datetime.month();
					uint8_t year = Global::Time::datetime.year();
					if(month == ::Date::FEBRUARY && day > 28)
					{
						day = 28 + year & 0b11 != 0;
					}
					else if(day > 30
					  && (month == ::Date::APRIL || month == ::Date::JUNE || month == ::Date::SEPTEMBER
						|| month == ::Date::NOVEMBER)
					)
					{
						day = 30;
					}
					else if(day > 31)
					{
						day = 31;
					}

					if(day < 1)
					{
						day = 1;
					}
					Global::Time::datetime.day(day);

					buttons(Button::static_acknowledge);
					encoder.acknowledge();
					core0_state[-1].last_updated(millis());
				}
			}

			else if(buttons[Button::CENTER].has_changed())
			{
				core0_state.pop(2);

				buttons(Button::static_acknowledge);
				encoder.acknowledge();
			}

			else if(millis() - core0_state[-1].last_updated() >= 10000)
			{
				core0_state.pop(2);  // Home | Menu[Date] | Date[Day]

				buttons(Button::static_acknowledge);
				encoder.acknowledge();	
			}
		}
	}
}
