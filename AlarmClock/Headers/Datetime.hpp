

class Datetime
{
	private:
		uint8_t _year;
		uint8_t _month;
		uint8_t _day;

		unsigned long _start_of_day;

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

		Datetime(uint8_t year=2023, uint8_t month=8, uint8_t day=17);

		void set_time(uint8_t hour, uint8_t minute);
		void set_hour(uint8_t hour);
		void set_minute(uint8_t minute);

		operator Time();
		void operator!();
		void operator++();

		friend bool operator==(Alarm& alarm, Datetime& datetime);
		friend bool operator==(Datetime& datetime, Alarm& alarm);
};
