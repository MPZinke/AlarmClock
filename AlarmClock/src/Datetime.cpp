

#include "../Headers/Datetime.hpp"


Datetime::Datetime(uint8_t year/* =2023 */, uint8_t month/* =8 */, uint8_t day/* =17 */)
: _year{year}, _month{month}, _day{day}, _start_of_day{millis()}
{
	// assert(2000 < _year && _year < 2400);  // Since I didn't code the 400 year rule for leap years
	assert(0 < _month && _month < 13);
	assert(_day <= 28
		|| (_day <= 29 && _month == FEBRUARY && _year & 0b11 == 0)
		|| (_day <= 30 && _month != FEBRUARY)
		|| (_day <= 31 && ((_month <= JULY && _month & 0b1 == 1) || (AUGUST <= _month && _month & 0b1 == 0)))
	);
}


void set_time(uint8_t hour, uint8_t minute, uint8_t second/* =0 */)
{
	_start_of_day = millis() - (hour * 3600000) - (minute * 60000) - second;
}


void set_hour(uint8_t hour)
/*
NOTES: Zeroes seconds.
*/
{
	unsigned long current_timestamp = millis();
	unsigned long time_delta = current_timestamp - _start_of_day;
	// Start of Day = Current Timestamp in milliseconds - New Hour in milliseconds - Prior Minute in milliseconds
	// Can also use `_start_of_day = current_timestamp - (hour * 3600000) - (time_delta % 3600000) / 60000;`
	_start_of_day = current_timestamp - (hour * 3600000) - (time_delta - ((time_delta / 3600000) * 3600000)) / 60000;
}


void set_minute(uint8_t minute)
/*
NOTES: Zeroes seconds.
*/
{
	unsigned long current_timestamp = millis();
	unsigned long time_delta = current_timestamp - _start_of_day;
	// Start of Day = Current Timestamp in milliseconds - Prior Hour in milliseconds - Prior Minute in milliseconds
	_start_of_day = current_timestamp - ((time_delta / 3600000) * 3600000) - (minute * 60000);
}


Datetime::operator Time()
{
	return Time(_start_of_day);
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
	_start_of_day = millis();
	_day++;

	if(_day > 31
	// OR (Month is FEBRUARY, APRIL, JUNE, SEPTEMBER, NOVEMBER AND ...)
	|| ((_month == APRIL || _month == JUNE || _month == SEPTEMBER || _month == NOVEMBER) && _day > 30)
	// OR (Month is FEBRUARY AND (past the 29th OR not a leap year and past the 28th))
	|| (_month == FEBRUARY && (_day > 29 || (_day > 28 && _year & 0b11 != 0)))
	)
	{
		_day = 1;
		_month++;
		if(_month >= 13)
		{
			_month = 1;
			_year++;
		}
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
