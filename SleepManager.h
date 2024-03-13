#pragma once

#include "Sleeper.h"

class SleepManager {
    unsigned long lastPressed;
    static SleepManager* instance;

    SleepManager() {};
public:
    static SleepManager* getInstance();
    SleepManager(SleepManager &other) = delete;
    void operator=(const SleepManager &) = delete;

    void begin();
    void updatePress();
    void attemptToSleep(Sleeper& sleeper);
    void wakeup(Sleeper& sleeper);
};
