

class Time
{
	public:
		Time(unsigned long timestamp);
		Time(uint8_t hour=0, uint8_t minute=0, uint8_t second=0);

	private:
		uint8_t _hour;
		uint8_t _minute;
		uint8_t _second;
};
