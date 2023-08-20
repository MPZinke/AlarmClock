

#pragma once


#include "../Headers/Date.hpp"
#include "../Headers/Time.hpp"


class Display
{
	public:
		Display();

		operator Date&();
		operator Time&();

		void operator=(Time& right);

	private:
		Date _date;
		Time _time;	
};
