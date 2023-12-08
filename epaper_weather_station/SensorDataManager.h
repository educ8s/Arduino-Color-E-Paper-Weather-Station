#pragma once

struct SensorData {
    float temperature[24];
    float humidity[24];
    float pressure[24];
};

class SensorDataManager {
public:
    SensorDataManager();

    void initializeData();  // Initialize the SensorData struct
    void updateData(float temp, float hum, float press);  // Update the data arrays with new values
    SensorData sensorData;

private:

};