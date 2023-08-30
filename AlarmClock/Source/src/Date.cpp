

#include "../Headers/Date.hpp"


const uint8_t Date::DAYS_IN_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


Date::Date(uint16_t year/* =2023 */, uint8_t month/* =8 */, uint8_t day/* =17 */)
: _year{year}, _month{month}, _day{day}
{
	// assert(2000 < _year && _year < 2400);  // Since I didn't code the 400 year rule for leap years
	assert(0 < _month && _month < 13);
	assert(_day <= 28
		|| (_day <= 29 && _month == FEBRUARY && _year & 0b11 == 0)
		|| (_day <= 30 && _month != FEBRUARY)
		|| (_day <= 31 && ((_month <= JULY && _month & 0b1 == 1) || (AUGUST <= _month && _month & 0b1 == 0)))
	);
}

uint16_t Date::year()
{
	return _year;
}


uint8_t Date::month()
{
	return _month;
}


uint8_t Date::day()
{
	return _day;
}


void Date::year(uint16_t year)
{
	_year = year;
}


void Date::month(uint8_t month)
{
	_month = month;
}


void Date::day(uint8_t day)
{
	_day = day;
}


// ———————————————————————————————————————————————————— OPERATOR ———————————————————————————————————————————————————— //

Date& Date::operator=(Date& right)
{
	_year = right._year;
	_month = right._month;
	_day = right._day;

	return *this;
}


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


int32_t Date::operator-(Date& right)
{
	Date &later, &earlier;
	bool right_is_later = *this <= right;
	if(right_is_later)
	{
		later = right;
		earlier = *this;
	}
	else
	{
		later = *this;
		earlier = right;
	}

	int32_t days = 0;
	for(uint16_t year = earlier._year; year < later._year-1; year++)
	{
		days += 365;
		if(year % 4 == 0)
		{
			days += 1;
		}
	}

	for(uint8_t month = earlier._month; month != later._month; (month % 12)++)
	{
		days += DAYS_IN_MONTH[month-1];
		if(month == FEBRUARY && later._year % 4)
		{
			days += 1;
		}
	}

	day += later._day - earlier._day;
	return day * (right_is_later * -1 + !right_is_later * 1);
}


bool Date::operator==(Date& right)
{
	return _year == right._year && _month == right._month && _day == right._day;
}


bool Date::operator<=(Date& right)
{
	if(_year < right._year)
	{
		return true;
	}

	if(_year == right._year)
	{
		if(_month < right._month)
		{
			return true;
		}

		if(_month == right._month && _day <= right._day)
		{
			return true;
		}
	}

	return false;
}
