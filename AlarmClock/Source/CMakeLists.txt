add_executable(AlarmClock
	main.cpp
)

target_link_libraries(AlarmClock
	arduino-compat DFMiniMp3 freertos pico_stdlib
)

pico_add_extra_outputs(AlarmClock)
