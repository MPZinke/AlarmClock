

#pragma once


#include <stdint.h>


#include "../Headers/Alarm.hpp"


class AlarmSet
{
	public:
		AlarmSet();

		bool remove(uint8_t index);
		uint8_t size();

		AlarmSet& operator+=(Alarm& alarm);
		Alarm operator[](uint8_t index) const;  // Getter
		Alarm& operator[](uint8_t index);  // Setter

	private:
		static const uint8_t _max = 10;
		uint8_t _size = 0;
		Alarm _alarms[_max];
};
