#include <WiFi.h>

#include "EspNowSender.h"

void EspNowSender::begin() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    memcpy(peerInfo.peer_addr, receiverMac, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
       
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
    }
}

void EspNowSender::sendPayload (EspNowMessage& message) {
    esp_now_send(receiverMac, (uint8_t *) &message, sizeof(message));
} 
