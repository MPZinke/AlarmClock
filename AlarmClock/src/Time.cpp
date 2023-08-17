

#include "../Headers/Time.hpp"


Time::Time(unsigned long duration_seconds)
{
	_hour = duration_seconds / 3600;
	unsigned long hour_seconds = _hour * 3600;
	_minute = (duration_seconds - hour_seconds) / 60;
	_second = duration_seconds - hour_seconds - (_minute * 60);
}


// Time::Time()
// : _hour{0}, _minute{0}, _second{0}
// {}


Time::Time(uint8_t hour/* =0 */, uint8_t minute/* =0 */, uint8_t second/* =0 */)
// Time::Time(uint8_t hour=0, uint8_t minute=0, uint8_t second=0)
: _hour{hour}, _minute{minute}, _second{second}
{}


// ———————————————————————————————————————————————————— OPERATOR ———————————————————————————————————————————————————— //

Time::operator unsigned long() const
{
	return _hour * 3600 + _minute * 60 + _second;
}


Time Time::operator+(unsigned long duration_seconds)
{
	return Time((unsigned long)(*this) + duration_seconds);
}


Time& Time::operator+=(unsigned long duration_seconds)
{
	unsigned long time_seconds = (unsigned long)(*this) + duration_seconds;
	_hour = time_seconds / 3600;
	unsigned long hour_seconds = _hour * 3600;
	_minute = (time_seconds - hour_seconds) / 60;
	_second = time_seconds - hour_seconds - (_minute * 60);

	return (*this)
}


bool Time::operator==(Time& right)
{
	return _hour == right._hour && _minute == right._minute && _second == right._second;
}


bool Time::operator>(Time& right)
{
	if(_hour > right._hour)
	{
		return true;
	}

	if(_hour == right._hour)
	{
		if(_minute > right._minute)
		{
			return true;
		}

		if(_minute == right._minute && _second > right._second)
		{
			return true;
		}
	}
	
	return false;
}


bool Time::operator>=(Time& right)
{
	if(_hour > right._hour)
	{
		return true;
	}

	if(_hour == right._hour)
	{
		if(_minute > right._minute)
		{
			return true;
		}

		if(_minute == right._minute && _second >= right._second)
		{
			return true;
		}
	}
	
	return false;
}


bool Time::operator<(Time& right)
{
	if(_hour < right._hour)
	{
		return true;
	}

	if(_hour == right._hour)
	{
		if(_minute < right._minute)
		{
			return true;
		}

		if(_minute == right._minute && _second < right._second)
		{
			return true;
		}
	}
	
	return false;
}


bool Time::operator<=(Time& right)
{
	if(_hour < right._hour)
	{
		return true;
	}

	if(_hour == right._hour)
	{
		if(_minute < right._minute)
		{
			return true;
		}

		if(_minute == right._minute && _second <= right._second)
		{
			return true;
		}
	}
	
	return false;
}
