

class Button
{
	public:
		Button();
		Button(uint pin);

		void acknowledge();
		bool has_changed();
		void update();

		Button& operator=(Button right);

	private:
		uint pin = -1;
		bool _is_pressed = false;  // whether the button is currently being pressed

		// Describes whether the state change has been read/acknowledged. Bound to _last_released_date and 
		//  _last_released_timestamp to indicate that they have not been set. IE that the values are garbage.
		bool _acknowledged = true;
		Date _last_released_date;
		unsigned long _last_released_timestamp;
};

