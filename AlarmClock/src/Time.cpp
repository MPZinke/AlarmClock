

#include "../Headers/Time.hpp"


Time::Time(unsigned long timestamp)
{
	unsigned long time_delta = (millis() - timestamp) / 1000;  // seconds
	_hour{time_delta / 3600};
	_minute{(time_delta - (_hour * 3600)) / 60};
	_seconds{time_delta - {_hour * 3600 + _minute * 60}};
}


Time::Time(uint8_t hour=0, uint8_t minute=0, uint8_t second=0)
: _hour{hour}, _minute{minute}, _second{second}
{}
