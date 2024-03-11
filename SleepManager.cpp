#include <Arduino.h>

#include "Constants.h"
#include "SleepManager.h"
 
SleepManager* SleepManager::getInstance() {
    if (instance == nullptr) {
        instance = new SleepManager();
    }
    return instance;
}

void SleepManager::begin() {
    lastPressed = 0;
}

void SleepManager::updatePress() {
    lastPressed = millis();
}

void SleepManager::attemptToSleep(Matrix& matrix) { 
    if (millis() < lastPressed + SLEEP_TIMEOUT_MS) {
        return;
    }

    matrix.sleep();

    esp_sleep_enable_touchpad_wakeup();
    esp_light_sleep_start();

    wakeup(matrix);
}

void SleepManager::wakeup(Matrix& matrix) {
    lastPressed = millis();
    matrix.wakeup();
}