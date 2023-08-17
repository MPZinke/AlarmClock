

#include <stdint.h>


class Date
{
	private:
		uint8_t _year;
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

		Date(uint8_t year=2023, uint8_t month=8, uint8_t day=17);

		void operator++();
};
