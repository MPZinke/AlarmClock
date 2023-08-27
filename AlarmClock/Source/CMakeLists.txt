add_executable(AlarmClock
	main.cpp
)

target_link_libraries(AlarmClock arduino-compat DFMiniMp3 freertos pico_stdlib)

pico_enable_stdio_usb(AlarmClock 1)
pico_enable_stdio_uart(AlarmClock 0)

pico_add_extra_outputs(AlarmClock)
