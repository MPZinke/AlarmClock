

#include "../Headers/Alarm.hpp"


#include <Arduino.h>


#include "../Headers/Datetime.hpp"
#include "../Headers/Time.hpp"


Alarm::Alarm()
: _hour{0xFF}, _minute{0xFF}, _last_dismissed{0}
{}


Alarm::Alarm(uint8_t hour, uint8_t minute)
: _hour{hour}, _minute{minute}, _last_dismissed{millis() / 60000}
{
	assert(hour < 24);
	assert(minute < 60);
}


uint8_t Alarm::hour()
{
	return _hour;
}


void Alarm::hour(uint8_t new_hour)
{
	_hour = new_hour;
}


uint8_t Alarm::minute()
{
	return _minute;
}


void Alarm::minute(uint8_t new_minute)
{
	_minute = new_minute;
}


void Alarm::dismiss()
{
	_last_dismissed = millis();
}


Alarm& Alarm::operator=(Alarm& right)
{
	_hour = right._hour;
	_minute = right._minute;
	_last_dismissed = right._last_dismissed;

	return *this;
}


bool Alarm::operator==(Alarm& right)
{
	return _hour == right._hour && _minute == right._minute;
}


bool operator==(Alarm& alarm, Time& time)
{
	return alarm._hour == time._hour && alarm._minute == time._minute;
}


bool operator==(Time& time, Alarm& alarm)
{
	return alarm._hour == time._hour && alarm._minute == time._minute;
}
