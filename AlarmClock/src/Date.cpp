

#include "../Headers/Date.hpp"


Date::Date(uint8_t year/* =2023 */, uint8_t month/* =8 */, uint8_t day/* =17 */)
: _year{year}, _month{month}, _day{day}
{}


void Date::operator++()
/*
NOTES: Ignores the 400 year rule for leap years.
*/
{
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
