#pragma once

#include "EspNow.h"

#include <esp_now.h>

class EspNowSender : public EspNow {
    esp_now_peer_info_t peerInfo;
public:
    void begin();
    void sendPayload (EspNowMessage& message);   
};
