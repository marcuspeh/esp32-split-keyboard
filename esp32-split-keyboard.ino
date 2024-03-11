#include "BatteryLevel.h"
#include "BleConnectionManager.h"
#include "BleKeyboard.h"
#include "Constants.h"
#include "Matrix.h"

BleKeyboard bleKeyboard;
BatteryLevel batteryLevel;
Matrix matrix;

void setup() {
  BleConnectionManager::getBleConnectionManager()->begin();

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
    float percentage = batteryLevel.caclulateBatteryLevel();
    bleKeyboard.setBatteryLevel(percentage);
  }

  matrix.keyScan(bleKeyboard);
}
