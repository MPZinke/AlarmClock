

#pragma once


#include "Date.hpp"
#include "Time.hpp"


#include <stdint.h>


class Alarm;


class Datetime: public Date, public Time
{
	private:
		unsigned long _start_of_day;  // Seconds

	public:
		Datetime(uint8_t year=2023, uint8_t month=8, uint8_t day=17);

		void set_time(uint8_t hour, uint8_t minute, uint8_t second=0);
		void set_hour(uint8_t hour);
		void set_minute(uint8_t minute);

		operator Date();
		operator Time();
		Datetime& operator=(unsigned long timestamp);
		void operator++();

		friend bool operator==(Alarm& alarm, Datetime& datetime);
		friend bool operator==(Datetime& datetime, Alarm& alarm);
};
