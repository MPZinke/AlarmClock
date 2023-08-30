

#pragma once


typedef uint8_t State;


namespace States
{
	enum
	{
		UPDATE_DISPLAY,
		HOME,
		SETTING_DATETIME_YEAR,
		SETTING_DATETIME_MONTH,
		SETTING_DATETIME_DAY,
		SETTING_DATETIME_HOUR,
		SETTING_DATETIME_MINUTE,
		SETTING_ALARM_HOUR,
		SETTING_ALARM_MINUTE,
		START_ALARM,
		PLAYING_ALARM,
		STOP_ALARM
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
