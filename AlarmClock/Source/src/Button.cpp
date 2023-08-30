

#include "../Headers/Button.hpp"


Button::Button()
: _pin{-1}, _is_pushed{false}
{}


Button::Button(uint pin)
: _pin{pin}
{
	gpio_set_dir(_pin, GPIO_IN);
	_is_pushed = gpio_pull(_pin);
}


void acknowledge()
{
	_acknowledged = true;
}


void Button::update()
{
	bool current_pull = gpio_pull(gpio);
	if(_is_pushed)
	{
		if(!current_pull)
		{
			_last_released_date = Global::Time::datetime;
			_last_released_timestamp = millis();
			_is_pushed = false;
			_acknowledged = false;
		}
	}
	else if(/* !_is_pushed && */ current_pull)
	{
		_is_pushed = true;
	}
}


Button& operator=(Button right)
{
	if(_pin == -1)
	{
		gpio_set_dir(right)
	}
}


void Button::static_acknowledge(Button& button)
{
	button.acknowledge();
}
