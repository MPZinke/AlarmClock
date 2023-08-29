

#pragma once


#include <stdint.h>


#include "States.hpp"


class Alarm;


template<size_t S, class T>
class StaticList
{
	public:
		StaticList();
		StaticList(T start_value);

		size_t max();
		T peek();
		T pop();
		bool remove(int index);
		uint8_t size();

		StaticList& operator+=(T value);
		T operator[](int index) const;  // Getter
		T& operator[](int index);  // Setter

	private:
		uint8_t _size = 0;
		T _values[S];
};
