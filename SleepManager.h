#pragma once

#include "Sleeper.h"

class SleepManager {
    unsigned long lastPressed;

public:
    SleepManager() {};
    void begin();
    void updatePress();
    void attemptToSleep(Sleeper& sleeper);
    void wakeup(Sleeper& sleeper);
};
