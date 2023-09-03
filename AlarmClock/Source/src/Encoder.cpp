
/***********************************************************************************************************************
*                                                                                                                      *
*   created by: MPZinke                                                                                                *
*   on 2023.08.28                                                                                                      *
*                                                                                                                      *
*   DESCRIPTION: TEMPLATE                                                                                              *
*   BUGS:                                                                                                              *
*   FUTURE:                                                                                                            *
*                                                                                                                      *
***********************************************************************************************************************/


#include "../Headers/Encoder.hpp"


#include <Arduino.h>


#include "../Headers/Global.hpp"


const int8_t Encoder::PULLS[4][4] = {
	{ 0, -1,  1,  0},
	{ 1,  0,  0, -1},
	{-1,  0,  0,  1},
	{ 0,  1, -1,  0}
};


Encoder::Encoder(uint8_t A_pin, uint8_t B_pin)
: _A_pin{A_pin}, _B_pin{B_pin}
{
	gpio_set_dir(_A_pin, GPIO_IN);
	gpio_set_dir(_B_pin, GPIO_IN);
}


void Encoder::acknowledge()
{
	_acknowledged = true;
	_change = 0;
}


int16_t Encoder::change()
{
	return _change;
}


bool Encoder::has_changed()
{
	return !_acknowledged;
}


unsigned long Encoder::last_changed()
{
	return _last_changed;
}


void Encoder::update()
{
	uint8_t A_pull = (uint8_t)gpio_get(_A_pin);
	uint8_t B_pull = (uint8_t)gpio_get(_B_pin);
	uint8_t new_pull = A_pull << A | B_pull << B;

	int8_t change = PULLS[_pull][new_pull];
	_change += change;
	_pull = new_pull;

	if((_change <= -2 || 2 <= _change) && change != 0)
	{
		_acknowledged = false;
		_last_changed = millis();
	}
}
