


class Encoder
{
	public:
		Encoder(uint8_t A_pin, uint8_t B_pin);

		void acknowledge();
		bool has_changed();
		unsigned long last_changed();
		void update();

	private:
		enum Bit
		{
			A = 0,
			B
		};

		static const int8_t PULLS[4][4];

		const uint8_t _A_pin;
		const uint8_t _B_pin;


		bool _acknowledged = true;
		unsigned long _last_change;
		int32_t _change = 0;  // Position change since last acknowledge
		uint8_t _pull;  // 0b000000BA
};
