#include "EEPROMManager.h"

EEPROMManager::EEPROMManager(int size) : eepromSize(size) {

}

void EEPROMManager::begin() {
  EEPROM.begin(eepromSize);
}

void EEPROMManager::clear() {
    for (int i = 0; i < eepromSize; ++i) {
        EEPROM.write(i, 0);
    }
    EEPROM.commit();
}

void EEPROMManager::saveWeatherId(int id) {
    EEPROM.put(500, id);
    EEPROM.commit();
    delay(100);

    Serial.println(readWeatherId());
}

int EEPROMManager::readWeatherId() {
    int number = 0;
    EEPROM.get(500, number);
    return number;
}



