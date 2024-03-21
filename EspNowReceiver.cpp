#include <esp_now.h>
#include <WiFi.h>

#include "EspNowReceiver.h"

void EspNowReceiver::begin() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb([](const uint8_t * mac, const uint8_t *incomingData, int len) -> void { onDataRecv(max, incomingData, len); });
}

void EspNowReceiver::onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    EspNowMessage msg;
    memcpy(&msg, incomingData, sizeof(msg));

    bleKeyboard->press(msg.keyPressed);
}


void EspNowReceiver::setBleKeyboard(BleKeyboard* bleKeyboard) {
    this->bleKeyboard = bleKeyboard;
}
