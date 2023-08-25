

#pragma once


#include "../Headers/Datetime.hpp"


#include "Arduino.h"


#include "../Headers/Alarm.hpp"



Datetime::Datetime(uint8_t year/* =2023 */, uint8_t month/* =8 */, uint8_t day/* =17 */)
: Date{Date(year, month, day)}, Time{Time()}, _start_of_day{millis()}
{
	// assert(2000 < _year && _year < 2400);  // Since I didn't code the 400 year rule for leap years
	assert(0 < _month && _month < 13);
	assert(_day <= 28
		|| (_day <= 29 && _month == FEBRUARY && _year & 0b11 == 0)
		|| (_day <= 30 && _month != FEBRUARY)
		|| (_day <= 31 && ((_month <= JULY && _month & 0b1 == 1) || (AUGUST <= _month && _month & 0b1 == 0)))
	);
}


uint8_t Datetime::hour() const
{
	return _hour;
}


uint8_t Datetime::minute() const
{
	return _minute;
}


uint8_t Datetime::second() const
{
	return _second;
}


void Datetime::time(uint8_t hour, uint8_t minute, uint8_t second/* =0 */)
{
	_start_of_day = millis() - (hour * 3600000) - (minute * 60000) - (second * 1000);
}


void Datetime::hour(uint8_t hour)
/*
NOTES: Zeroes seconds.
*/
{
	unsigned long current_timestamp = millis();
	unsigned long time_delta = current_timestamp - _start_of_day;
	// Start of Day = Current Timestamp in seconds - New Hour in seconds - Prior Minute in seconds
	// Can also use `_start_of_day = current_timestamp - (hour * 3600000) - (time_delta % 3600000) / 60000;`
	_start_of_day = current_timestamp - (hour * 3600000) - (time_delta - ((time_delta / 3600000) * 3600000)) / 60000;

	_hour = hour;
}


void Datetime::minute(uint8_t minute)
/*
NOTES: Zeroes seconds.
*/
{
	unsigned long current_timestamp = millis();
	unsigned long time_delta = current_timestamp - _start_of_day;
	// Start of Day = Current Timestamp in seconds - Prior Hour in seconds - Prior Minute in seconds
	_start_of_day = current_timestamp - ((time_delta / 3600000ul) * 3600000ul) - (minute * 60000ul);

	_minute = minute;
}


void Datetime::second(uint8_t second)
{
	unsigned long current_timestamp = millis();
	unsigned long time_delta = current_timestamp - _start_of_day;
	unsigned long prior_hour_milliseconds = (time_delta / 3600000ul) * 3600000ul;
	unsigned long prior_minute_milliseconds = ((time_delta - prior_hour_milliseconds) / 60000ul) * 60000ul;
	// Start of Day = Current Timestamp in seconds - Prior Hour in seconds - Prior Minute in seconds
	_start_of_day = current_timestamp - prior_hour_milliseconds - prior_minute_milliseconds - (second * 1000ul);

	_second = second;
}


Datetime::operator Time&()
{
	return *this;
}


Datetime& Datetime::operator=(unsigned long current_timestamp)
{
	unsigned long current_time = current_timestamp - _start_of_day;
	if(current_time >= 86400000ul)
	{
		Date::operator++();
		_start_of_day += 86400000ul;
		current_time = current_timestamp - _start_of_day;
	}

	Time::operator=(current_time / 1000ul);
	return *this;
}


void Datetime::operator++()
/*
NOTES: Ignores the 400 year rule for leap years.
*/
{
	unsigned long current_timestamp = millis();
	unsigned long current_time = current_timestamp - _start_of_day;
	if(current_time >= 86400000ul)
	{
		Date::operator++();
		_start_of_day += 86400000ul;
		current_time = current_timestamp - _start_of_day;
	}

	Time::operator=(current_time / 1000ul);
}
