
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


int8_t Encoder::change()
{
	uint8_t new_pull = (uint8_t)gpio_is_pulled_down(_A_pin) << A | (uint8_t)gpio_is_pulled_down(_A_pin) << B;
	if(_pull == new_pull)
	{
		return 0;
	}

	_last_move_date = Global::Time::datetime;
	_last_move_timestamp = millis();
	_position += PULLS[_pull][new_pull];
	_pull = new_pull;

	return PULLS[_pull][new_pull];
}
