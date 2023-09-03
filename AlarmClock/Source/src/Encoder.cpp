
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


void Encoder::update(uint pin, uint32_t events)
{
	using namespace Global::Inputs;
	uint8_t new_pull = ((uint8_t)gpio_get(encoder._A_pin) << A) | ((uint8_t)gpio_get(encoder._B_pin) << B);
	encoder._change += PULLS[encoder._pull][new_pull];
	encoder._pull = new_pull;

	if(encoder._change <= -2 || 2 <= encoder._change)
	{
		encoder._acknowledged = false;
		encoder._last_changed = millis();
	}
}
