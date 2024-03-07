#include <Arduino.h>

#include "Constants.h"

class BatteryLevel {
    unsigned long nextScanTime = 0;

    float caclulateBatteryVoltage(float anologReadin);
    int readAnalogData();
public:
    void begin();
    long caclulateBatteryLevel();
    bool shouldUpdateBatteryLevel();
}
