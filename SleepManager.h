#include "Matrix.h"

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
    void attemptToSleep(Matrix& matrix);
    void wakeup(Matrix& matrix);
};
