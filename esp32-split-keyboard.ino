// uncomment the following line for main board.
// #define MAIN_BOARD

#include "BatteryLevel.h"
#include "BleConnectionManager.h"
#include "BleKeyboard.h"
#include "Constants.h"
#include "MainMatrix.h"

#if defined(MAIN_BOARD)
#include "EspNowRecevier.h"
#else
#include "EspNowSender.h"
#endif


BleKeyboard bleKeyboard;
BatteryLevel batteryLevel;
MainMatrix matrix;

#if defined(MAIN_BOARD)
EspNowRecevier espNowController;
#else
EspNowSender espNowController;
#endif

void setup() {
  BleConnectionManager* bleConnectionManager = new BleConnectionManager();

  bleConnectionManager->begin();
  batteryLevel.begin();
  bleKeyboard.begin();
  matrix.begin();
  espNowController.begin();

  // Injet dependencies
  matrix.setBleConnectionManager(bleConnectionManager);
  matrix.setBleKeyboard(&bleKeyboard);
#if defined(MAIN_BOARD)
  espNowController.setBleKeyboard(&bleKeyboard);
#endif

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

  matrix.keyScan();
}
