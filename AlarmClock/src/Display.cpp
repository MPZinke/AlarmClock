

#include "../Headers/Display.hpp"


#include "../Headers/Date.hpp"
#include "../Headers/Time.hpp"


Display::Display()
: _date{Date()}, _time{Time()}
{}


Display::operator Date&()
{
	return _date;
}


Display::operator Time&()
{
	return _time;
}


void Display::operator=(Time& right)
{
	_time = right;
}

