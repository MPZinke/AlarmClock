

#pragma once


#include <Adafruit_ThinkInk.h>


#include "../Headers/Global.hpp"


#include "../Headers/Date.hpp"
#include "../Headers/Time.hpp"


class Datetime;


class Display
{
	public:
		static const uint16_t RENDER_TIME;

		enum Default
		{
			EINK_DC=27,
			EINK_RESET=21,
			EINK_CS=17,
			EINK_SRAM_CS=26,
			EINK_BUSY=20
		};

		Display();
		Display(Datetime& datetime);
		Display(Time time);
		Display(Date& date, Time& time);

		void begin();
		void update();

		operator Date&();
		operator Time&();

		Display& operator=(Date& right);
		Display& operator=(Time& right);

	private:
		Date _date;
		ThinkInk_154_Mono_D67 _eInk;
		Date _last_update_date;  // Used to prevent refreshing too frequently
		unsigned long _last_update_timestamp;  // Used to prevent refreshing too frequently
		Time _time;

		void print_date();
		void print_time();

};
