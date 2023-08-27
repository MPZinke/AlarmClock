add_library(adafruit-busio INTERFACE)

target_sources(adafruit-busio INTERFACE
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_BusIO/Adafruit_I2CDevice.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_BusIO/Adafruit_SPIDevice.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_BusIO/Adafruit_BusIO_Register.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_BusIO/Adafruit_SPIDevice.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_BusIO/Adafruit_I2CDevice.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_BusIO/Adafruit_BusIO_Register.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_BusIO/Adafruit_I2CRegister.h"
)

target_include_directories(adafruit-busio INTERFACE
 "${CMAKE_CURRENT_LIST_DIR}/Adafruit_BusIO"
)

target_link_libraries(adafruit-busio INTERFACE
    arduino-compat
)
