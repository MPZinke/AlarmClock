

#include "../Headers/Core1.hpp"


#include <pico/multicore.h>


#include "../Headers/Global.hpp"


#include "../Headers/Display.hpp"
#include "../Headers/States.hpp"


namespace Core1
{
	void main()
	{
		States::State state = (States::State)multicore_fifo_pop_blocking();
		switch(state)
		{
			case(States::UPDATE_DISPLAY):
			{
				Core1::update_display();
			}
		}
	}


	void update_display()
	{
		Global::display.update();
	}
}
