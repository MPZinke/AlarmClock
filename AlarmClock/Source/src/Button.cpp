

#include "../Headers/Button.hpp"


#include <Arduino.h>


Button::Button()
: _pin{0xFF}, _is_pressed{false}
{}


Button::Button(uint pin)
: _pin{pin}
{
	gpio_set_dir(_pin, GPIO_IN);
	_is_pressed = gpio_get(_pin);
}


void Button::acknowledge()
{
	_acknowledged = true;
}


bool Button::has_changed()
{
	update();
	return !_acknowledged;
}


void Button::update()
{
	bool current_pull = gpio_get(_pin);
	if(_is_pressed)
	{
		if(!current_pull)
		{
			_last_released_timestamp = millis();
			_is_pressed = false;
			_acknowledged = false;
		}
	}
	else if(/* !_is_pressed && */ current_pull)
	{
		_is_pressed = true;
	}
}


Button& Button::operator=(Button right)
{
	if(_pin == 0xFF)
	{
		gpio_set_dir(right._pin, GPIO_IN);
	}

	return *this;
}


void Button::static_acknowledge(Button& button)
{
	button.acknowledge();
}
