
class Alarm
{
	private:
		uint8_t _hour;
		uint8_t _minute;

		bool _dismissed = false;

	public:
		Alarm(uint8_t hour, uint8_t minute);

		friend bool operator==(Alarm& alarm, Datetime& datetime);
		friend bool operator==(Datetime& datetime, Alarm& alarm);
};
