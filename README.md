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
Instead of having 2 ESP32-C3 for each side, I have decided to only have one ESP32-C3. This is mainly to simplify the project. However, this should be easily extended to have one main ESP32 and another to send keyscans to the main one using ESP-NOW.

## Battery level 
Since the ESP32-C3 board senses up to 3.3v pin, and li-ion battery has a voltage of 3.2v - 4.2v, voltage divider is used to determine the battery level.

```
(Battery +) --------|
                    |
                    R1
                    |
                    |----------- (Pin)
                    |
                    R2
                    |
(Battery -) --------|----------- (GND)

                                  R2
Value at pin = Battery Volts x ----------
                                R1 + R2
```
Based on how the voltage divider works, to caclualte the actual battery level, we will need to multiply the voltage read by the pin with
(R1 + R2) / R2.

## Inactive
ESP32-C3 will keep track of the time of the last key input and make use of that to calculate when the keyboard will go into light sleep. The time till light sleep can be updated in `constants.h` file.

Since ESP32-C3 is able to use any GPIO pin to wake up from light sleep, we will be checking if the columns pinout are HIGH (ie pressed).

## Tools used
* [keyboard layout](http://www.keyboard-layout-editor.com/)
* [keyboard plate](https://kbplate.ai03.com/)

## Credits

Credits to the creator and contributors of [BleKeyboard library](https://github.com/T-vK/ESP32-BLE-Keyboard).