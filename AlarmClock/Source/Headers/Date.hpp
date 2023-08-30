

#pragma once


#include <stdint.h>


class Date
{
	protected:
		uint16_t _year;
		uint8_t _month;
		uint8_t _day;

	public:
		enum
		{
			JANUARY=1,
			FEBRUARY=2,
			MARCH=3,
			APRIL=4,
			MAY=5,
			JUNE=6,
			JULY=7,
			AUGUST=8,
			SEPTEMBER=9,
			OCTOBER=10,
			NOVEMBER=11,
			DECEMBER=12
		};

		static const uint8_t DAYS_IN_MONTH[12];

		Date(uint16_t year=2023, uint8_t month=8, uint8_t day=17);

		uint16_t year();
		uint8_t month();
		uint8_t day();

		void year(uint16_t year);
		void month(uint8_t month);
		void day(uint8_t day);

		Date& operator=(Date& right);

		uint32_t operator-(Date& right);

		void operator++();
		bool operator==(Date& right);
		bool operator<=(Date& right);
};
