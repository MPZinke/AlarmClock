
class Alarm
{
	private:
		uint8_t _hour;
		uint8_t _minute;

	public:
		Alarm(uint8_t hour, uint8_t minute);

		operator unsigned long();

		friend bool operator==(Alarm& alarm, Datetime& datetime);
		friend bool operator==(Datetime& datetime, Alarm& alarm);
};


class AlarmInstance: Alarm
{
	private:
		uint8_t _timestamp;
		bool _deactivated = false;

	public:
		AlarmInstance(unsigned long timestamp);
		AlarmInstance(uint8_t hour, uint8_t minute, unsigned long _start_of_day);

		void update(unsigned long timestamp);
		void update(Datetime& datetime);
		void update(uint8_t hour, uint8_t minute);

		friend bool operator==(AlarmInstant& alarm_instance, Datetime& datetime);
		friend bool operator==(Datetime& datetime, AlarmInstant& alarm_instance);
};
