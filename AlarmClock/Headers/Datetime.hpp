

#pragma once


#define EPD_SPI &SPI0 // primary SPI


#include "Date.hpp"
#include "Time.hpp"


#include <stdint.h>


class Alarm;


class Datetime: public Date, public Time
{
	private:
		unsigned long _start_of_day;  // Milliseconds

	public:
		Datetime(uint8_t year=2023, uint8_t month=8, uint8_t day=17);

		uint8_t hour() const;
		uint8_t minute() const;
		uint8_t second() const;

		void time(uint8_t hour, uint8_t minute, uint8_t second=0);
		void hour(uint8_t new_hour);
		void minute(uint8_t new_minute);
		void second(uint8_t new_second);

		operator Time&();
		Datetime& operator=(unsigned long timestamp);
		void operator++();

		// friend bool operator==(Alarm& alarm, Datetime& datetime);
		// friend bool operator==(Datetime& datetime, Alarm& alarm);
};
