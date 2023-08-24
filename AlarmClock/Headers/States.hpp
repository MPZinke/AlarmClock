

#pragma once



namespace States
{
	enum State
	{
		DISPLAY_TIME,
		SET_TIME_HOUR,
		SET_TIME_MINUTE,
		SET_ALARM_HOUR,
		SET_ALARM_MINUTE,
		PLAY_ALARM,
		STOP_ALARM
	};

	void display_time();
	void set_time_hour();
	void set_time_minute();
	void set_alarm_hour();
	void set_alarm_minute();
	void play_alarm();
	void stop_alarm();
}
