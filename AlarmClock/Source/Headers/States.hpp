

#pragma once


typedef uint8_t State;


namespace States
{
	class State
	{
		public:
			State();  // For StaticList
			State(void(*state)());

			unsigned long last_updated();
			void last_updated(unsigned long timestamp);

			void operator()();

			State& operator=(State right);
			State& operator=(void(*right)());

			bool operator==(State& right);
			bool operator==(void(*right)());

			bool operator!=(State& right);
			bool operator!=(void(*right)());


		private:
			void(*_state)();
			unsigned long _last_updated;
	};


	namespace Home
	{
		void main();
		void adjust_audio();
		void set_menu();
	}


	namespace Menu
	{
		void alarm();
		void time();
		void date();
	}


	namespace Alarm
	{
		extern uint8_t SELECTED_ALARM;


		namespace Menu
		{
			void alarms();
			void new_alarm();
		}


		namespace Selected
		{
			void edit();
			void delete_alarm();


			namespace Edit
			{
				void hour();
				void minute();
			}
		}


		namespace Alarm
		{
			void start();
			void playing();
			void stop();
		}
	}


	namespace Time
	{
		void hour();
		void minute();
	}


	namespace Date
	{
		void year();
		void month();
		void day();
	}
}
