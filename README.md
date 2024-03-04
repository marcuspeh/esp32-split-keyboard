# ESP32 Split BLE Keyboard 

Split keyboard firmware written for ESP32. This makes use of `BleKeyboard` library from this [repo](https://github.com/T-vK/ESP32-BLE-Keyboard).

## Features

 - [x] Send key strokes
 - [x] Send text
 - [x] Press/release individual keys
 - [x] Media keys are supported
 - [x] See battery level
 - [x] Compatible with Android
 - [x] Compatible with Windows
 - [x] Compatible with Linux
 - [x] Compatible with MacOS 
 - [x] Compatible with iOS 

## Installation
- (Make sure you can use the ESP32 with the Arduino IDE. [Instructions can be found here.](https://github.com/espressif/arduino-esp32#installation-instructions))
- Download the master branch and flash `ESP32-BLE-KEYBOARD.ino`.

## Notes
Instead of having 2 ESP32 for each side, I have decided to only have one ESP32. This is mainly to simplify the project. However, this should be easily extended to have one main ESP32 and another to send keyscans to the main one using ESP-NOW.

## Credits

Credits to the creator and contributors of [BleKeyboard library](https://github.com/T-vK/ESP32-BLE-Keyboard).