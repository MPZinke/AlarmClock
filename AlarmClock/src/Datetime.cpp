

#include "../Headers/Datetime.hpp"


void Datetime::operator++()
{
	_second++;
	if(_second >= 60)
	{
		_second = 0;
		_minute++;
		if(_minute >= 60)
		{
			_minute = 0;
			_hour++;
			if(_hour >= 24)
			{
				_hour = 0;
				_day++;

				if(_day > 31
				|| (((_month < JULY && _month & 0b1 == 0) || (AUGUST < _month && _month & 0b1 == 1)) && _day > 30)
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
		}
	}
}


bool operator==(Alarm& alarm, Datetime& datetime)
{
	return alarm._hour == datetime._hour && alarm._minute == datetime._minute && alarm._dismissed == false;
}


bool operator==(Datetime& datetime, Alarm& alarm)
{
	return alarm == datetime;
}
