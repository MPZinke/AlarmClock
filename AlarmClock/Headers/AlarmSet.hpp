

#include "Alarm.hpp"


class AlarmSet
{
	public:
		AlarmSet();

		uint8_t size();

		AlarmSet operator+=(Alarm alarm);
		Alarm operator[](uint8_t index) const;  // Getter
		Alarm& operator[](uint8_t index);  // Setter

	private:
		Alarm _alarms[10];
		Alarm _count = 0;
}
