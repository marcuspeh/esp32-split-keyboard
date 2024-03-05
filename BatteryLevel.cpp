#include <Arduino.h>

#include "BatteryLevel.h"
#include "Constants.h"

void  BatteryLevel::begin() {
    pinMode(PIN_BATTERY_LEVEL, INPUT);
}

long BatteryLevel::caclulateBatteryLevel() {
    int anologReadin = readAnalogData();
    float volts = caclulateBatteryLevel(anologReadin);
    float dividerDiff = MAX_DIVIDER_VOLT - MIN_DIVIDER_VOLT;
    float batteryDiff = MAX_BATTERY_VOLT - MIN_BATTERY_VOLT;
    
    return (volts - MIN_DIVIDER_VOLT) / dividerDiff * batteryDiff + MIN_BATTERY_VOLT;
}

float BatteryLevel::caclulateBatteryVoltage(float anologReadin) {
    float totalResistance = RESISTOR_RESISTANCE_1 + RESISTOR_RESISTANCE_2;
    float voltAtPin = anologReadin * VOLT_PER_ANOLOG_VALUE;
    return voltAtPin * totalResistance / RESISTOR_RESISTANCE_2;
}

int BatteryLevel::readAnalogData() {
    return analogRead(PIN_BATTERY_LEVEL);
}


bool BatteryLevel:: shouldUpdateBatteryLevel() {
    // Time will overflow back to 0 around every 50 days. Doesn't really matter here since
    // the keyboard is not going to be switched on for that long.
    unsinged long currTime = millis();
    if (currTime < prevTime + BATTERY_SCAN_INTERVAL_MS) {
        return false;
    }
    prevTime = currTime;
    return true;
}
