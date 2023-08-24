

#include "../Headers/Display.hpp"


#include "../Headers/Date.hpp"
#include "../Headers/Time.hpp"


#define EPD_SPI &SPI0 // primary SPI


const uint16_t Display::RENDER_TIME = 2000;  // 2 Seconds


Display::Display(uint8_t eInk_DC, uint8_t eInk_reset, uint8_t eInk_CS, uint8_t eInk_SRAM_CS, uint8_t eInk_busy)
: _date{Date(2024, 9, 1)}, _eInk{ThinkInk_154_Mono_D67(eInk_DC, eInk_reset, eInk_CS, eInk_SRAM_CS, eInk_busy)}, _time{Time(24, 12)}
{}


Display::operator Date&()
{
	return _date;
}


Display::operator Time&()
{
	return _time;
}


Display& Display::operator=(Time& right)
{
	_time = right;
}


void Display::begin()
{
	_eInk.begin(THINKINK_MONO);
}


void Display::update()
{
	_eInk.clearBuffer();

	print_date();
	print_time();
	_eInk.display();
	delay(2000);
}


void Display::print_date()
{
	char date_text[6] = "00-00";
	date_text[0] = _date.month() / 10 + '0';
	date_text[1] = _date.month() - (_date.month() / 10 * 10) + '0';

	date_text[3] = _date.day() / 10 + '0';
	date_text[4] = _date.day() - (_date.day() / 10 * 10) + '0';

	_eInk.setTextSize(3);
	if(date_text[0] == '0')
	{
		_eInk.setCursor(74, 35);
		_eInk.print(date_text+1);
	}
	else
	{
		_eInk.setCursor(65, 35);
		_eInk.print(date_text);
	}
}


void Display::print_time()
{
	char time_text[6] = "00:00";
	time_text[0] = _time.hour() / 10 + '0';
	time_text[1] = _time.hour() - (_time.hour() / 10 * 10) + '0';

	time_text[3] = _time.minute() / 10 + '0';
	time_text[4] = _time.minute() - (_time.minute() / 10 * 10) + '0';

	_eInk.setTextSize(6);
	if(time_text[0] == '0')
	{
		_eInk.setCursor(47, 79);
		_eInk.print(time_text+1);
	}
	else
	{
		_eInk.setCursor(10, 79);
		_eInk.print(time_text);
	}
}
