


class Encoder
{
	public:
		Encoder(uint8_t A_pin, uint8_t B_pin);


	private:
		enum Bit
		{
			A = 0,
			B
		};

		static const int8_t PULLS[4][4];

		const uint8_t _A_pin;
		const uint8_t _B_pin;

		Date _late_move_date;
		unsigned long _last_move_timestamp;

		int _position = 0;
		uint8_t _pull;  // 0b000000BA

		uint8_t change();
};
