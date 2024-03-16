#include <Arduino.h>

#include "Constants.h"
#include "SleepManager.h"
 
void SleepManager::begin() {
    lastPressed = 0;
}

void SleepManager::updatePress() {
    lastPressed = millis();
}

void SleepManager::attemptToSleep(Sleeper& sleeper) { 
    if (millis() < lastPressed + SLEEP_TIMEOUT_MS) {
        return;
    }

    sleeper.sleep();

    esp_sleep_enable_touchpad_wakeup();
    esp_light_sleep_start();

    wakeup(sleeper);
}

void SleepManager::wakeup(Sleeper& sleeper) {
    lastPressed = millis();
    sleeper.wakeup();
}