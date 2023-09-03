

#include <pico/stdlib.h>


class Button
{
	public:
		enum ButtonListIndexMapping
		{
			MENU,
			TOP,
			RIGHT,
			BOTTOM,
			LEFT
		};

		Button();
		Button(uint pin);

		void acknowledge();
		bool has_changed();
		static void static_acknowledge(Button& button);
		void update();

		Button& operator=(Button right);

	private:
		uint _pin = -1;
		bool _is_pressed = false;  // whether the button is currently being pressed

		// Describes whether the state change has been read/acknowledged. Bound to _last_released_date and 
		//  _last_released_timestamp to indicate that they have not been set. IE that the values are garbage.
		bool _acknowledged = true;
		unsigned long _last_released_timestamp;
};


