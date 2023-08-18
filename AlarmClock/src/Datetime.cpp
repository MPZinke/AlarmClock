

#include "../Headers/Datetime.hpp"


#include "Arduino.h"


Datetime::Datetime(uint8_t year/* =2023 */, uint8_t month/* =8 */, uint8_t day/* =17 */)
: Date{Date(year, month, day)}, Time{Time()}, _start_of_day{millis() / 1000}
{
	// assert(2000 < _year && _year < 2400);  // Since I didn't code the 400 year rule for leap years
	assert(0 < _month && _month < 13);
	assert(_day <= 28
		|| (_day <= 29 && _month == FEBRUARY && _year & 0b11 == 0)
		|| (_day <= 30 && _month != FEBRUARY)
		|| (_day <= 31 && ((_month <= JULY && _month & 0b1 == 1) || (AUGUST <= _month && _month & 0b1 == 0)))
	);
}


void Datetime::set_time(uint8_t hour, uint8_t minute, uint8_t second/* =0 */)
{
	_start_of_day = millis() - (hour * 3600) - (minute * 60) - second;
}


void Datetime::set_hour(uint8_t hour)
/*
NOTES: Zeroes seconds.
*/
{
	unsigned long current_timestamp = millis() / 1000;
	unsigned long time_delta = current_timestamp - _start_of_day;
	// Start of Day = Current Timestamp in seconds - New Hour in seconds - Prior Minute in seconds
	// Can also use `_start_of_day = current_timestamp - (hour * 3600000) - (time_delta % 3600000) / 60000;`
	_start_of_day = current_timestamp - (hour * 3600) - (time_delta - ((time_delta / 3600) * 3600)) / 60;
}


void Datetime::set_minute(uint8_t minute)
/*
NOTES: Zeroes seconds.
*/
{
	unsigned long current_timestamp = millis() / 1000;
	unsigned long time_delta = current_timestamp - _start_of_day;
	// Start of Day = Current Timestamp in seconds - Prior Hour in seconds - Prior Minute in seconds
	_start_of_day = current_timestamp - ((time_delta / 3600) * 3600) - (minute * 60);
}


Datetime::operator Time()
{
	return Time((millis() / 1000) - _start_of_day);
}


void Datetime::operator!()
/*
SUMMARY: Zeroes the time.
*/
{
	_start_of_day = millis();
}


void Datetime::operator++()
/*
NOTES: Ignores the 400 year rule for leap years.
*/
{
	Time::operator++();
	if(Time::operator==(0))
	{
		Date::operator++();
		_start_of_day = millis();
	}
}


bool operator==(Alarm& alarm, Datetime& datetime)
{

	return alarm == (Time)datetime && alarm._dismissed == false;
}


bool operator==(Datetime& datetime, Alarm& alarm)
{
	return alarm == datetime;
}
