#include "Constants.h"

class BleConnectionManager {
    const unsigned char macAddress[MAX_DEVICES][6] = {
        {0x35, 0xAF, 0xA4, 0x07, 0x0B, 0x66},
        {0x31, 0xAE, 0xAA, 0x47, 0x0D, 0x61},
        {0x31, 0xAE, 0xAC, 0x42, 0x0A, 0x31}
    };
    static BleConnectionManager* instance;

    BleConnectionManager() {};
public:
    static BleConnectionManager* getInstance();
    BleConnectionManager(BleConnectionManager &other) = delete;
    void operator=(const BleConnectionManager &) = delete;

    void begin();
    void changeID(int deviceNumber);
};
