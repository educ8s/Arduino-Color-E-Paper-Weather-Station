#include "SensorDataManager.h"

SensorDataManager::SensorDataManager() {
  
}

void SensorDataManager::initializeData() {
    for (int i = 0; i < 24; ++i) {
        sensorData.temperature[i] = 0.0; 
        sensorData.humidity[i] = 0.0;    
        sensorData.pressure[i] = 0.0;
    }
}

void SensorDataManager::updateData(float temp, float hum, float press) {
    // Shift the existing data to make room for the new values
    for (int i = 0; i < 23; ++i) {
        sensorData.temperature[i] = sensorData.temperature[i + 1];
        sensorData.humidity[i] = sensorData.humidity[i + 1];
        sensorData.pressure[i] = sensorData.pressure[i + 1];
    }

    // Update the last element with the new values
    sensorData.temperature[23] = temp;
    sensorData.humidity[23] = hum;
    sensorData.pressure[23] = press;
}