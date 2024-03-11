#include "Constants.h"

class BatteryLevel {
    unsigned long nextScanTime = 0;

    float caclulateBatteryVoltage(int anologReadin);
public:
    void begin();
    long caclulateBatteryLevel();
    bool shouldUpdateBatteryLevel();
};
