
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


const int8_t Encoder::PULLS = {
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


unsigned long Encoder::last_change()
{
	return _last_change;
}


void Encoder::update(uint pin, uint32_t events)
{
	_acknowledged = false;
	_last_change = millis();

	uint8_t new_pull = (uint8_t)gpio_is_pulled_down(_A_pin) << A | (uint8_t)gpio_is_pulled_down(_A_pin) << B;
	_change += PULLS[_pull][new_pull];
	_pull = new_pull;
}
