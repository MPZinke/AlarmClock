

#include <pico/multicore.h>


#include "../Headers/Global.hpp"


#include "../Headers/Display.hpp"


#define EPD_SPI &SPI0 // primary SPI


namespace Core1
{
	void update_display()
	{
		Global::display.update();
	}
}
