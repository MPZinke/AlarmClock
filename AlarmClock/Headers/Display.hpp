

#pragma once


#include <Adafruit_ThinkInk.h>


#include "../Headers/Global.hpp"


#include "../Headers/Date.hpp"
#include "../Headers/Time.hpp"


class Display
{
	public:
		static const uint16_t RENDER_TIME;

		Display(uint8_t eInk_DC=4, uint8_t eInk_reset=7, uint8_t eInk_CS=17, uint8_t eInk_SRAM_CS=5,
			uint8_t eInk_busy=10, MbedSPI& spi=Global::Hardware::SPI1
		);

		void begin();
		void update();

		operator Date&();
		operator Time&();

		Display& operator=(Date& right);
		Display& operator=(Time& right);

	private:
		Date _date;
		ThinkInk_154_Mono_D67 _eInk;
		Time _time;

		void print_date();
		void print_time();

};
