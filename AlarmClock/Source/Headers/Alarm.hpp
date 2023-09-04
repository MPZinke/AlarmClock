

#pragma once


#include <stdint.h>


class Time;


class Alarm
{
	private:
		uint8_t _hour;
		uint8_t _minute;

		unsigned long _last_dismissed;
		// The timestamp at which an alarm was last dismissed. Used to determine when 

	public:
		Alarm();
		Alarm(uint8_t hour, uint8_t minute);

		uint8_t hour();
		void hour(uint8_t new_hour);
		uint8_t minute();
		void minute(uint8_t new_minute);

		void dismiss();

		Alarm& operator=(unsigned long duration_seconds);
		Alarm& operator=(Alarm& right);

		bool operator==(Alarm& alarm);
		friend bool operator==(Alarm& alarm, Time& time);
		friend bool operator==(Time& time, Alarm& alarm);
};
