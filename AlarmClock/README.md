# Setup & Run Instructions
Based from: https://learnembeddedsystems.co.uk/freertos-on-rp2040-boards-pi-pico-etc-using-vscode


## Install

```bash
brew install cmake arm-none-eabi-gcc
```


## Setup
Starting in the base directory
```bash
cd AlarmClock/

git clone https://github.com/raspberrypi/pico-sdk.git
# git -C pico-sdk/ checkout 6a7db34ff6334
git -C pico-sdk/ submodule update --init

git -C arduino-compat/ clone https://github.com/earlephilhower/arduino-pico.git
git -C arduino-compat/arduino-pico/ checkout cf63040
git -C arduino-compat/arduino-pico/ submodule update --init


git -C Adafruit/ clone https://github.com/adafruit/Adafruit_EPD.git
# git -C Adafruit/Adafruit_EPD checkout 08571489fba
git -C Adafruit/ clone https://github.com/adafruit/Adafruit-GFX-Library.git
# git -C Adafruit/Adafruit-GFX-Library checkout 83a182d260
git -C Adafruit/ clone https://github.com/adafruit/Adafruit_BusIO.git
# git -C Adafruit/Adafruit_BusIO checkout 3ea940b7453


git -C DFMiniMp3/ clone https://github.com/Makuna/DFMiniMp3.git
# git -C DFMiniMp3/DFMiniMp3 checkout 07117383aa

git -C FreeRTOS/ clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git
git -C FreeRTOS/FreeRTOS-Kernel/ checkout smp
# git -C FreeRTOS/FreeRTOS-Kernel/ checkout 570ade4001e5

cp ../Other/Assets/FreeRTOS/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/include/portmacro.h FreeRTOS/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/include/portmacro.h
cp ../Other/Assets/FreeRTOS/FreeRTOS-Kernel/tasks.c FreeRTOS/FreeRTOS-Kernel/tasks.c
```

## Build
Starting from <base directory>/AlarmClock
```bash
mkdir build
cd build
cmake .. -DPICO_SDK_PATH=../pico-sdk
make
```


## Library Installation
https://github.com/fhdm-dev/pico-arduino-compat/tree/master
