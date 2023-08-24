

#include "../Headers/Alarm.hpp"


#define EPD_SPI &SPI0 // primary SPI


Alarm::Alarm(uint8_t hour, uint8_t minute)
: _hour{hour}, _minute{minute}
{}


// AlarmInstance::AlarmInstance(unsigned long alarm_timestamp)
// : _hour{}, , _timestamp{alarm_timestamp}
// {}

// AlarmInstance::AlarmInstance(uint8_t hour, uint8_t minute, unsigned long start_of_day)
// {}
