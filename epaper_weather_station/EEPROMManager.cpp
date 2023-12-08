#include "EEPROMManager.h"

EEPROMManager::EEPROMManager(int size) : eepromSize(size) {}

bool EEPROMManager::isInitialized() {
  if(EEPROM.read(initFlagAddress) != 0) {
    return true; }
}

void EEPROMManager::begin() {
    EEPROM.begin(eepromSize);
    bootUpCount = EEPROM.read(initFlagAddress);
    Serial.print("Bootup count: ");
    Serial.println(bootUpCount);

    if (bootUpCount > 1000) {
        Serial.println("Bootup count exceeded 1000. Resetting the counter...");
        resetBootupCount();
    } 

    if (!isInitialized()) {
        clear();
    }
}

void EEPROMManager::resetBootupCount() {
    EEPROM.write(initFlagAddress, 1);
    EEPROM.commit();
}

void EEPROMManager::incrementBootupCount() {
    bootUpCount++;
    EEPROM.write(initFlagAddress, bootUpCount);
    EEPROM.commit();
}

void EEPROMManager::clear() {
    
    for (int i = 0; i < eepromSize; ++i) {
        EEPROM.write(i, 0);
    }
    EEPROM.commit();
    delay(10);
}

void EEPROMManager::write(int address, uint8_t data) {
    EEPROM.write(address, data);
}

uint8_t EEPROMManager::read(int address) {
    return EEPROM.read(address);
}

void EEPROMManager::setInitialized() {
    EEPROM.write(initFlagAddress, 1);
    EEPROM.commit();
    delay(10);  // Add a delay to ensure the write operation completes
}

void EEPROMManager::saveSensorData(const SensorData& data) {
    int address = initFlagAddress + sizeof(uint8_t);  // Skip the initialization flag

    for (int i = 0; i < 24; ++i) {
        EEPROM.put(address, data.temperature[i]);
        address += sizeof(float);

        EEPROM.put(address, data.humidity[i]);
        address += sizeof(float);

        EEPROM.put(address, data.pressure[i]);
        address += sizeof(float);
    }
        EEPROM.commit();
}

void EEPROMManager::loadSensorData(SensorData& data) {
    int address = initFlagAddress + sizeof(uint8_t);  // Skip the initialization flag

    for (int i = 0; i < 24; ++i) {
        EEPROM.get(address, data.temperature[i]);
        address += sizeof(float);

        EEPROM.get(address, data.humidity[i]);
        address += sizeof(float);

        EEPROM.get(address, data.pressure[i]);
        address += sizeof(float);
    }
}

void EEPROMManager::clearBootUpCount() {
    EEPROM.begin(eepromSize);
    bootUpCount = 0;
    EEPROM.write(initFlagAddress, bootUpCount);
    EEPROM.commit();
}

void EEPROMManager::saveWeatherId(int id) {
    EEPROM.put(500, id);
    EEPROM.commit();
    delay(10);
}

int EEPROMManager::readWeatherId() {
    int number = 0;
    EEPROM.get(500, number);
    return number;
}