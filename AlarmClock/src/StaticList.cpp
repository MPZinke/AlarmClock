

// FROM: https://cplusplus.com/articles/1C75fSEw/


#include <Arduino.h>


#include "../Headers/Alarm.hpp"
#include "../Headers/States.hpp"



template<size_t S, class T>
class StaticList
{
	public:
		StaticList()
		{}

		StaticList(T start_value)
		{
			_values[0] = start_value;
			_size = 1;
		}

		size_t max()
		{
			return S;
		}

		T peek()
		{
			assert(_size != 0);

			return _values[_size-1];
		}

		T pop()
		{
			assert(_size != 0);

			_size--;
			return _values[_size];
		}

		bool remove(uint8_t index)
		{
			if(index >= _size)
			{
				return false;
			}

			for(uint8_t current_index = index; current_index < _size - 1; current_index++)
			{
				_values[current_index] = _values[current_index+1];
			}

			_size--;
			return true;
		}

		uint8_t size()
		{
			return _size;
		}

		StaticList& operator+=(T value)
		{
			// Keep it safe and only add a value if there is room
			if(_size != S)
			{
				_values[_size] = value;
				_size++;
			}

			return *this;
		}

		T operator[](uint8_t index) const  // Getter
		{
			assert(index < _size);

			return _values[index];
		}

		T& operator[](uint8_t index)  // Setter
		{
			assert(index < _size);

			if(index >= _size)
			{
				if(_size == S)
				{
					index = S - 1;  // Keep index within bounds
				}
				else
				{
					index = _size;  // Increment index
				}
			}

			return _values[index];
		}

	private:
		uint8_t _size = 0;
		T _values[S];
};


template class StaticList<10, Alarm>;
template class StaticList<3, States::State>;
