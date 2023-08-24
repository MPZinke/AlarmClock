

#include <pico/multicore.h>


#include "../Headers/Global.hpp"


#include "../Headers/Display.hpp"



namespace Core1
{
	void update_display()
	{
		Global::display.update();
	}
}
