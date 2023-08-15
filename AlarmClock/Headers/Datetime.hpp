class Datetime
{
	private:
		uint8_t _year;
		uint8_t _month;
		uint8_t _day;

		uint8_t _hour;
		uint8_t _minute;
		uint8_t _second;

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

		Datetime(uint8_t year=2023, uint8_t month=8, uint8_t day=17, uint8_t hour=0, uint8_t minute=0,
			uint8_t second=0
		);

		void operator++();

		friend bool operator==(Alarm& alarm, Datetime& datetime);
		friend bool operator==(Datetime& datetime, Alarm& alarm);
};
