

#pragma once


#include <stdint.h>


#include "States.hpp"


class Alarm;


template<class T>
class List
{
	public:
		List();
		List(T start_value);

		T peek();
		T pop();
		bool remove(uint8_t index);
		uint8_t size();

		List& operator+=(T value);
		T operator[](uint8_t index) const;  // Getter
		T& operator[](uint8_t index);  // Setter

	private:
		static const uint8_t _max = 10;
		uint8_t _size = 0;
		T _values[_max];
};
