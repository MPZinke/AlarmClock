

class Datetime;
class Display;


namespace Global
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

	extern State state;
	extern ::Datetime datetime;
	extern ::Display display;
}
