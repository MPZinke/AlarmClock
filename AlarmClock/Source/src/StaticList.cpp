

// FROM: https://cplusplus.com/articles/1C75fSEw/


#include <Arduino.h>


#include "../Headers/Alarm.hpp"
#include "../Headers/Button.hpp"
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

		StaticList(T start_value0, T start_value1, ...)
		{
			_values[0] = start_value0;
			_values[1] = start_value1;
			for(uint x = 2; x < S; x++)
			{
				va_list variable_list;
				va_start(variable_list, start_value1);
				T temp = va_arg(variable_list, T);
				_values[x] = temp;
			}
		}

		void operator()(void(*function)(T& value))
		{
			for(uint32_t x = 0; x < _size; x++)
			{
				function(_values[x]);
			}
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

		void pop(size_t amount)
		{
			assert(_size >= amount);

			_size -= amount;
		}

		void push(T value)
		{
			// Keep it safe and only add a value if there is room
			if(_size != S)
			{
				_values[_size] = value;
				_size++;
			}
		}

		bool remove(int index)
		{
			while(index < 0)
			{
				index = _size + index;  // EG. `index = 7 + -1;`
			}

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
			push(value);
			return *this;
		}

		T operator[](int index) const  // Getter
		{
			while(index < 0)
			{
				index = _size + index;  // EG. `index = 7 + -1;`
			}

			assert(index < _size);

			return _values[index];
		}

		T& operator[](int index)  // Setter
		{
			while(index < 0)
			{
				index = _size + index;  // EG. `index = 7 + -1;`
			}

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
template class StaticList<5, Button>;
template class StaticList<10, States::State>;
