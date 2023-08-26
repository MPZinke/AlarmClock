add_executable(test
	main.cpp
)

target_link_libraries(test
	pico_stdlib freertos
)

pico_add_extra_outputs(test)
