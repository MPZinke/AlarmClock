

#pragma once


#include <pico/stdlib.h>
#include <stdint.h>


class Encoder
{
	public:
		Encoder(uint8_t A_pin, uint8_t B_pin);

		void acknowledge();
		int16_t change();
		bool has_changed();
		unsigned long last_changed();
		void update();

	private:
		enum Bit
		{
			A = 1,
			B = 0
		};

		static const int8_t PULLS[4][4];

		const uint8_t _A_pin;
		const uint8_t _B_pin;


		bool _acknowledged = true;
		int16_t _change = 0;  // Position change since last acknowledge
		unsigned long _last_changed;
		uint8_t _pull;  // 0b000000BA
};
