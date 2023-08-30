

#pragma once


typedef uint8_t State;


namespace States
{
	enum
	{
		HOME,
		MENU_ALARM,
		MENU_TIME,
		MENU_DATE,

		ALARM_MENU,
		ALARM_MENU_NEW,
		ALARM_EDIT,
		ALARM_DELETE,
		ALARM_HOUR,
		ALARM_MINUTE,

		START_ALARM,
		PLAYING_ALARM,
		STOP_ALARM,

		TIME_HOUR,
		TIME_MINUTE,

		DATE_YEAR,
		DATE_MONTH,
		DATE_DAY,
	};

	class State
	{
		public:
			State(::State state);

			unsigned long start_time();

			operator uint8_t();

		private:
			uint8_t _state;
			unsigned long _start_time;
	};

	void display_time();
	void set_time_hour();
	void set_time_minute();
	void set_alarm_hour();
	void set_alarm_minute();
	void start_alarm();
	void playing_alarm();
	void stop_alarm();
}
