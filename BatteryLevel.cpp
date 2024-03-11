#include <Arduino.h>

#include "BatteryLevel.h"

void  BatteryLevel::begin() {
    pinMode(PIN_BATTERY_LEVEL, INPUT);
}

long BatteryLevel::caclulateBatteryLevel() {
    int anologReadin = analogRead(PIN_BATTERY_LEVEL);
    float volts = caclulateBatteryVoltage(anologReadin);
    float dividerDiff = MAX_DIVIDER_VOLT - MIN_DIVIDER_VOLT;
    float batteryDiff = MAX_BATTERY_VOLT - MIN_BATTERY_VOLT;
    
    return (volts - MIN_DIVIDER_VOLT) / dividerDiff * batteryDiff + MIN_BATTERY_VOLT;
}

float BatteryLevel::caclulateBatteryVoltage(int anologReadin) {
    float totalResistance = RESISTOR_RESISTANCE_1 + RESISTOR_RESISTANCE_2;
    float voltAtPin = anologReadin * VOLT_PER_ANOLOG_VALUE;
    return voltAtPin * totalResistance / RESISTOR_RESISTANCE_2;
}

bool BatteryLevel:: shouldUpdateBatteryLevel() {
    // Time will overflow back to 0 around every 50 days. Doesn't really matter here since
    // the keyboard is not going to be switched on for that long.
    unsigned long currTime = millis();
    if (currTime >= nextScanTime) { 
        nextScanTime = currTime + BATTERY_SCAN_INTERVAL_MS;
        return false;
    }
    return true;
}
