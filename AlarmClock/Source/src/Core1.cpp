

#include "../Headers/Core1.hpp"


#include <pico/multicore.h>


#include "../Headers/Global.hpp"


// #include "../Headers/Display.hpp"
#include "../Headers/States.hpp"


namespace Core1
{
	void update_display()
	{
		Global::display.update();
	}
}
