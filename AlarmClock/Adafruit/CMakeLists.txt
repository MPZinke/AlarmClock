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

add_library(adafruit-gfx-library INTERFACE)

target_sources(adafruit-gfx-library INTERFACE
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Adafruit_GFX.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Adafruit_GrayOLED.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Adafruit_SPITFT.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/examples/GFXcanvas/GFXcanvasSerialDemo.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/glcdfont.c"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/fontconvert/fontconvert.c"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Adafruit_SPITFT.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/gfxfont.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Adafruit_GrayOLED.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Adafruit_SPITFT_Macros.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Adafruit_GFX.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerifBold24pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSansBoldOblique9pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/Picopixel.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSansBoldOblique18pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSans24pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMonoBold12pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMonoOblique18pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSans9pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerif24pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMono9pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMonoBold9pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMonoOblique9pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerifBoldItalic9pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerifBold12pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMonoBoldOblique12pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSansOblique24pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSansBold9pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMono24pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/Org_01.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerifBold18pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSansBold12pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMonoBoldOblique18pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerifItalic18pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerifBoldItalic18pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMonoBold18pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMono12pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSansBoldOblique12pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMonoOblique12pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSansBold18pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSans18pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSansBold24pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerif9pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerif18pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSansOblique18pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSans12pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerifItalic9pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/TomThumb.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/Tiny3x3a2pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerifItalic12pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSansBoldOblique24pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerif12pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMonoOblique24pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerifItalic24pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSansOblique12pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMonoBoldOblique9pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMonoBoldOblique24pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMonoBold24pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSansOblique9pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerifBoldItalic24pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeMono18pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerifBold9pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/Fonts/FreeSerifBoldItalic12pt7b.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library/examples/GFXcanvas/GFXcanvasSerialDemo.h"
)

target_include_directories(adafruit-gfx-library INTERFACE
 "${CMAKE_CURRENT_LIST_DIR}/Adafruit-GFX-Library"
)

target_link_libraries(adafruit-gfx-library INTERFACE
    arduino-compat
    adafruit-busio
)

add_library(adafruit-epd INTERFACE)

target_sources(adafruit-epd INTERFACE
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/Adafruit_MCPSRAM.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/Adafruit_EPD.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_SSD1619.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_ACeP.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_SSD1675.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_EK79686.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_UC8276.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_SSD1608.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_SSD1680.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_IL0373.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_UC8151D.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_IL0398.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_SSD1675B.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_IL91874.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_SSD1681.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/Adafruit_EPD.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/Adafruit_MCPSRAM.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/Adafruit_ThinkInk.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_290_Grayscale4_T5.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_213_Mono_B73.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_290_Tricolor_RH.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_154_Tricolor_Z90.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_270_Tricolor_Z70.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_420_Mono_BN.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_420_Tricolor_Z21.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_270_Grayscale4_W3.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_213_Grayscale4_T5.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_290_Mono_M06.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_154_Mono_D67.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_290_Tricolor_Z13.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_420_Tricolor_RW.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_213_Mono_BN.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_213_Tricolor_RW.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_213_Mono_M21.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_154_Mono_M10.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_420_Grayscale4_T2.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_213_Tricolor_Z16.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_420_Mono_M06.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_154_Tricolor_Z17.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_154_Tricolor_RW.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_154_Grayscale4_T8.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_290_Mono_BN.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_290_Tricolor_Z10.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_270_Tricolor_C44.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_154_Mono_D27.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/panels/ThinkInk_213_Mono_B72.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_SSD1608.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_UC8151D.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_SSD1675.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_SSD1619.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_IL91874.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_EK79686.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_IL0398.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_ACeP.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_IL0373.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_SSD1680.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_UC8276.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_SSD1681.h"
  "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src/drivers/Adafruit_SSD1675B.h"
)

target_include_directories(adafruit-epd INTERFACE
 "${CMAKE_CURRENT_LIST_DIR}/Adafruit_EPD/src"
)

target_link_libraries(adafruit-epd INTERFACE
    arduino-compat
    adafruit-gfx-library
    adafruit-busio
)
