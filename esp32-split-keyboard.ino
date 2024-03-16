#include "BatteryLevel.h"
#include "BleConnectionManager.h"
#include "BleKeyboard.h"
#include "SleepManager.h"
#include "Constants.h"
#include "Matrix.h"

BleKeyboard bleKeyboard;
BatteryLevel batteryLevel;
Matrix matrix;

void setup() {
  BleConnectionManager* bleConnectionManager = new BleConnectionManager();
  SleepManager* sleepManager = new SleepManager();

  sleepManager->begin();
  bleConnectionManager->begin();
  batteryLevel.begin();
  bleKeyboard.begin();
  matrix.begin();

  // Injet dependencies
  matrix.setBleConnectionManager(bleConnectionManager);
  matrix.setSleepManager(sleepManager);
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
