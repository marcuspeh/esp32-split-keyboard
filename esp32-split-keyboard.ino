/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include "BleKeyboard.h"

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void loop() {
  if(bleKeyboard.isConnected()) {
   //
   // Below is an example of pressing multiple keyboard modifiers 
   // which by default is commented out.
    Serial.println("Sending Ctrl+Alt+Delete...");
    bleKeyboard.press(KEY_LEFT_SHIFT);
    delay(100);
    bleKeyboard.releaseAll();
  } else {
    Serial.println("Not connected");
  }

  Serial.println("Waiting 5 seconds...");
  delay(5000);
}
