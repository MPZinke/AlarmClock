

#include "../Headers/AlarmSet.hpp"


AlarmSet::AlarmSet()
{}


bool AlarmSet::remove(uint8_t index)
{
	if(index >= _size)
	{
		return false;
	}

	for(uint8_t current_index = index; current_index < _size - 1; current_index++)
	{
		_alarms[current_index] = _alarms[current_index+1];
	}

	_size--;
	return true;
}


uint8_t AlarmSet::size()
{
	return _size;
}


AlarmSet& AlarmSet::operator+=(Alarm& alarm)
{
	if(_size != _max)
	{
		_alarms[_size] = alarm;
		_size++;
	}

	return *this;
}


Alarm AlarmSet::operator[](uint8_t index) const  // Getter
{
	if(index >= _size)
	{
		index = _size - 1;
	}

	return _alarms[index];
}


Alarm& AlarmSet::operator[](uint8_t index)  // Setter
{
	if(index >= _size)
	{
		if(_size == _max)
		{
			index = _max - 1;  // Keep index within bounds
		}
		else
		{
			index = _size;  // Increment index
		}
	}

	return _alarms[index];
}