#include "Constants.h"

class BleConnectionManager {
    static constexpr const uint8_t MacAddress[MAX_DEVICES][6] = {
        {0x35, 0xAF, 0xA4, 0x07, 0x0B, 0x66},
        {0x31, 0xAE, 0xAA, 0x47, 0x0D, 0x61},
        {0x31, 0xAE, 0xAC, 0x42, 0x0A, 0x31}
    };
    static constexpr BleConnectionManager* bleConnectionManager = nullptr;

public:
    static void begin();
    static void changeID(int deviceNumber);
};
