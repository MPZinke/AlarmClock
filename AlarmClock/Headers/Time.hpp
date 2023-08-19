

#pragma once


#include <stdint.h>


class Display;


class Time
{
	public:
		Time(unsigned long duration_seconds);
		Time(uint8_t hour=0, uint8_t minute=0, uint8_t second=0);

		uint8_t hour() const;
		uint8_t minute() const;
		uint8_t second() const;

		// ———— OPERATORS ———— //
		operator unsigned long() const;

		Time& operator=(unsigned long duration_seconds);
		Time& operator=(Time& right);
		void operator++();

		Time operator+(unsigned long duration_seconds) const;
		Time& operator+=(unsigned long duration_seconds);

		bool operator==(unsigned long duration_seconds) const;
		bool operator==(Time& right) const;
		friend bool operator==(unsigned long duration_seconds, Time& right);
		bool operator>(Time& right) const;
		bool operator>=(Time& right) const;
		bool operator<(Time& right) const;
		bool operator<=(Time& right) const;

	private:
		uint8_t _hour;
		uint8_t _minute;
		uint8_t _second;
};
