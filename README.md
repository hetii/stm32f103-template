Easy "clone and go" repository for stm32f103 mcu, based on [libopencm3-template](https://github.com/libopencm3/libopencm3-template).

This template repository contains also 4KB of USB MSC (Mass Storage Class) bootloader.<br>
Bootloader part was written by [Piotr Gozdur](https://github.com/piotr-go).<br>
Check LICENSE file and his awasome [DIY-A586](https://github.com/piotr-go/DIY-A586) fpga based amiga project.<br>

# Preparation
 1. `git clone --recurse-submodules git@github.com:hetii/stm32f103-template.git your-project`
 2. `cd your-project`
 3. `make -C libopencm3` # (Only needed once)

# Bootloader installation
 1. Check if you need change something in src/Makefile
 2. Connect your mcu to usb-to-serial board, RX to pin A9, TX to pin A10.<br>
    Additionaly set jumpers BOOT0 to 1 and BOOT1 to 0.
![Image](https://www.electrosoftcloud.com/wp-content/uploads/2020/11/STM32F103_programming_circuit.jpg.webp)
 3. Flash bootloader by: `make -C src bootloaderflash`
 4. Disconnect device and set both jumpers to 0.
 5. Plug usb cable to PC. Your PC should detect new storage device with one file.
![Image](https://obrazki.elektroda.pl/1531676400_1465306758.png)

# Project build and flash
 1. Build project: `make -C src`
 2. Copy binary firmware to usb storage: `make -C src mscflash`

If you have an older git, or got ahead of yourself and skipped the ```--recurse-submodules```
you can fix things by running ```git submodule update --init``` (This is only needed once)

# Directories
* lib/bootloader contains 4kB size msc (Mass Storage Class) bootloader binary.
* src contains your application.
* lib contains something shared.

# Bluepill pinout
![Image](https://www.electrosoftcloud.com/wp-content/uploads/2020/12/STM32-Pin-Details_0.png)

# As a template
You should replace this with your _own_ README if you are using this
as a template.
