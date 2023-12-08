#include "EEPROM.h"

class EEPROMManager {
public:
    EEPROMManager(int size);
    void begin();
    void clear();
    void saveWeatherId(int id);
    int readWeatherId();
    
private:
    int eepromSize;
    int initFlagAddress = 0;  // Address for initialization flag
};