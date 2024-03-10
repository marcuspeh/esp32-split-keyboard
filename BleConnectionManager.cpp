#include <EEPROM.h>  

#include "BleConnectionManager.h"

void BleConnectionManager::begin() {
    EEPROM.begin(4);                                      
    int deviceChose = EEPROM.read(0);                  
    esp_base_mac_addr_set(&MacAddress[deviceChose][0]); 
}

void BleConnectionManager::changeID(int deviceNumber) {
    if(deviceNumber >= MAX_DEVICES || EEPROM.read(0) == deviceNumber) {
        return;
    }
    
    EEPROM.write(0, deviceNumber);
    EEPROM.commit();
    esp_sleep_enable_timer_wakeup(1);
    esp_deep_sleep_start(); 
}