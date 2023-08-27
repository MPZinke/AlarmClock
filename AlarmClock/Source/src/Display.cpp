

#include "../Headers/Display.hpp"


#include "../Headers/Global.hpp"


#include "../Headers/Date.hpp"
#include "../Headers/Time.hpp"
#include "../Headers/Datetime.hpp"



const uint16_t Display::RENDER_TIME = 2000;  // 2 Seconds


Display::Display(Datetime& datetime)
: _eInk{ThinkInk_154_Mono_D67(EINK_DC, EINK_RESET, EINK_CS, EINK_SRAM_CS, EINK_BUSY, &SPI)}
{
	_date = (Date&)datetime;
	_time = (Time&)datetime;
}


Display::operator Date&()
{
	return _date;
}


Display::operator Time&()
{
	return _time;
}


Display& Display::operator=(Date& right)
{
	_date = right;

	return *this;
}


Display& Display::operator=(Time& right)
{
	_time = right;

	return *this;
}


void Display::begin()
{
	_eInk.begin(THINKINK_MONO);
}


void Display::update()
{
	_eInk.clearBuffer();
	_eInk.setTextColor(EPD_BLACK);

	_eInk.drawCircle(100, 100, 115, EPD_BLACK);
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
		_eInk.setCursor(30, 79);
		_eInk.print(time_text+1);
	}
	else
	{
		_eInk.setCursor(10, 79);
		_eInk.print(time_text);
	}
}
