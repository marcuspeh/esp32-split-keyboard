#include "BleKeyboard.h"
#include "Constants.h"
#include "Matrix.h"

BleKeyboard bleKeyboard;
BatteryLevel batteryLevel;
Matrix matrix;

void setup() {
  batteryLevel.begin();
  bleKeyboard.begin();
  matrix.begin();
}

void loop() {
  if(!bleKeyboard.isConnected()) {
    delay(300);
    return;
  }
  
  if (batteryLevel.shouldUpdateBatteryLevel()) { 
    float batteryLevel = caclulateBatteryLevel();
    bleKeyboard.setBatteryLevel(batteryLevel);
    prevTime = currTime;
  }

  matrix.keyScan(bleKeyboard);
}
