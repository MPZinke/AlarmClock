

#pragma once


typedef uint8_t State;


namespace States
{
	class State
	{
		public:
			State();
			State(::State state);

			unsigned long start_time();

			operator uint8_t();

		private:
			uint8_t _state;
			unsigned long _start_time;
	};


	enum
	{
		NONE,
		HOME,
		MENU_ALARM,
		MENU_TIME,
		MENU_DATE,

		ALARM_MENU_ALARMS,  // Alarm[SELECTED_ALARM] option of alarms menu highlighted
		ALARM_MENU_NEW,  // New option of alarms menu highlighted
		ALARM_SELECTED_EDIT,  // Edit option of selected alarm highlighted
		ALARM_SELECTED_DELETE,  // Deleted option of selected alarm highlighted
		ALARM_SELECTED_HOUR,  // Set hour of selected alarm
		ALARM_SELECTED_MINUTE,  // Set minute of selected alarm

		START_ALARM,
		PLAYING_ALARM,
		STOP_ALARM,

		TIME_HOUR,
		TIME_MINUTE,

		DATE_YEAR,
		DATE_MONTH,
		DATE_DAY,
	};


	namespace Home
	{
		void main();
		void adjust_audio();
		void set_menu();
	}


	namespace Menu
	{
		enum
		{
			ALARM=MENU_ALARM,
			TIME=MENU_TIME,
			DATE=MENU_DATE
		};


		void alarm();
		void time();
		void date();
	}


	namespace Alarm
	{
		extern uint8_t SELECTED_ALARM;


		namespace Menu
		{
			enum
			{
				ALARMS=ALARM_MENU_ALARMS,
				NEW=ALARM_MENU_NEW
			};


			void alarms();
			void new_alarm();
		}


		namespace Seletected
		{
			enum
			{
				EDIT=ALARM_SELECTED_EDIT,
				DELETE=ALARM_SELECTED_DELETE
			};


			void delete_alarm();
			void edit();


			namespace Edit
			{
				enum
				{
					HOUR=ALARM_SELECTED_HOUR,
					MINUTE=ALARM_SELECTED_MINUTE
				};


				void hour();
				void minute();
			}
		}


		namespace Alarm
		{
			enum
			{
				START=States::START_ALARM,
				PLAYING=States::PLAYING_ALARM,
				STOP=States::STOP_ALARM,
			};


			void start_alarm();
			void playing_alarm();
			void stop_alarm();
		}
	}


	namespace Time
	{
		enum
		{
			HOUR=TIME_HOUR,
			MINUTE=TIME_MINUTE
		};


		void hour();
		void minute();
	}


	namespace Date
	{
		enum
		{
			YEAR=DATE_YEAR,
			MONTH=DATE_MONTH,
			DAY=DATE_DAY
		};


		void year();
		void month();
		void day();
	}
}
