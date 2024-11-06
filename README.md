# Nucleus ESP: An Affordable Hacking Tool

Nucleus ESP is a budget-friendly, yellow gadget for various hacking applications. It can transmit in the Sub-GHz RF range and has additional potential, which I plan to test further.

## Project Overview

I modified the device by desoldering the RGB diode to use it as GPIO, and repurposed the LCD backlight pin for the CC1101 chip select (CS) function.  
This is my first project in C, which I began in early summer with some background in PHP and a bit of FPGA tinkering. I'm learning as I go, figuring things out by experimenting.

**Status**: Work in Progress (WIP)  
Please go easy on it; it's still evolving!

## Features Implemented

With the help of my Software-Defined Radio (SDR), I implemented a RAW protocol for replay through a simple bit-bang method, upgrading it to more precise timing later (previously, I sampled every 430 microseconds).

Now, I’m planning to reintegrate RCswitch and the `.sub` (Flipper) file player from the old GUI, as they haven’t been added to the new interface yet.

**Last Stable Version**: Compiled into bin files. Occasionally, things may break in new versions, so for consistent testing, use this stable version.

### Last Commit Status
- **Updated to new LVGL**: This was not so easy.  
- **Touch drivers**: I remembered why I use bitbang drivers while moving to new LVGL - drivers included, should compile from source.  
- **New file browser**: Unlike previous one, this one is usable, even with bare hand.  
- **SubGhz files transmission**: When system starts transmitting, it freez and unfreeze after transmiting, but most raw timing files will transmit.

### Priority List
- Saving of subGhz files  
- Parsing of custom protocol data from subGhz files and writing them to CC1101 registers to make those work

### Current Functionalities
- **CC1101 RAW Replay**: Now operates similarly to the Flipper. (Saving not working; will repair, high priority)  
- **`.sub` Files Player**: Supports RAW files, tested with AM270 and AM650.  
- **Tesla Charger Opener**: Currently deactivated; will come back later, not a priority.  
- **Large `.sub` File Support**: Handles virtually unlimited file sizes, tested with a 3MB "Came_top_brute.sub" file.  
- **Brute Force Attack on 8-bit RF Codes**: Experimental feature for the M1E IC by MOSDESIGN SEMICONDUCTOR CORP. [M1E Datasheet](https://www.cika.com/soporte/Information/Semiconductores/CIencoder-decoder/M1E-MOSDESIGN.pdf)

### Planned Features
- Bluetooth Spam  
- Sour Apple  
- Wi-Fi Deauther  
- Bad USB  
- 2.4GHz Support  
- MouseJack Attack  

## Timing and Transmission Quality

The timing tolerance is around 1-5 microseconds. Transmission quality from `.sub` files is as follows:

### AM270
![AM270 Transmission](https://github.com/GthiN89/NucleusESP32/blob/main/images/AM270.PNG)

### AM650
![AM650 Transmission](https://github.com/GthiN89/NucleusESP32/blob/main/images/AM650.PNG)

### Capture Times
![Capture Times](https://github.com/GthiN89/NucleusESP32/blob/main/images/capture%20times.bmp)

## Hardware
- Cheap Yellow Display (CYD)  
- ESP32-2432S028R  
- ESP32-2432S028Rv2  

Happy hacking!
