cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(AlarmClock)

pico_sdk_init()

add_subdirectory(FreeRTOS)
add_subdirectory(Source AlarmClock-Source)
add_subdirectory(DFMiniMp3)
add_subdirectory(arduino-compat)
add_subdirectory(Adafruit)
