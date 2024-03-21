#pragma once

#include "EspNow.h"
#include "BleKeyboard.h"
#include "Matrix.h"

class EspNowReceiver : public EspNow {
    BleKeyboard* bleKeyboard;

public:
    void begin();
    void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
    void setBleKeyboard(BleKeyboard* bleKeyboard);
};
