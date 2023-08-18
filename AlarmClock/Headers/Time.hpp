

#pragma once


#include <stdint.h>


class Time
{
	public:
		Time(unsigned long duration_seconds);
		// Time();
		Time(uint8_t hour=0, uint8_t minute=0, uint8_t second=0);

		uint8_t hour();
		uint8_t minute();
		uint8_t second();

		// ———— OPERATORS ———— //
		operator unsigned long() const;

		void operator++();

		Time operator+(unsigned long duration_seconds);
		Time& operator+=(unsigned long duration_seconds);

		bool operator==(unsigned long duration_seconds);
		bool operator==(Time& right);
		friend bool operator==(unsigned long duration_seconds, Time& right);
		bool operator>(Time& right);
		bool operator>=(Time& right);
		bool operator<(Time& right);
		bool operator<=(Time& right);

	private:
		uint8_t _hour;
		uint8_t _minute;
		uint8_t _second;
};
