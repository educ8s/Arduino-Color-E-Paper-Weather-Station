#include "EEPROM.h"
#include "SensorDataManager.h"

class EEPROMManager {
public:
    EEPROMManager(int size);
    void begin();  
    void saveSensorData(const SensorData& data);
    void loadSensorData(SensorData& data);
    void clearBootUpCount();
    int bootUpCount = 0;
    void clear();       
    void saveWeatherId(int id);
    int readWeatherId();
    void incrementBootupCount();
    
private:
    int eepromSize;
    int initFlagAddress = 0;  // Address for initialization flag

    bool isInitialized();  // Check if EEPROM is initialized
    void setInitialized(); // Set the initialization flag
   
    void write(int address, uint8_t data);
    uint8_t read(int address);
    void resetBootupCount();
};