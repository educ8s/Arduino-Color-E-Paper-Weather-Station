#include "sensors.h"
#include "display.h"
#include "EEPROMManager.h"
#include "SensorDataManager.h"
#include "ForecastManager.h"

#define TIME_TO_SLEEP  360  //Time to sleep in seconds

char* ssid     = "yourSSID";      // SSID of local network
char* password = "yourPassword";  // Password on network
char* APIKEY = "yourAPIKEY";
char* cityID = "253394"; //Sparta, Greece

Sensors sensors(13);
Display display;
EEPROMManager memory(512);
SensorDataManager sensorData;
ForecastManager forecast;

void setup() {
  Serial.begin(115200);
  sensors.begin();
  memory.begin();
  sensors.readSensors();
  sensorData.initializeData();
  memory.loadSensorData(sensorData.sensorData);


  display.begin();

    //Every 6 hours, get the Weather Forecast
  if(memory.bootUpCount %60 == 0) {
    forecast.begin(ssid, password);
    forecast.getForecast(cityID, APIKEY);
    memory.saveWeatherId(forecast.id);
  } else {
    forecast.id = memory.readWeatherId();
  }

  //Every Hour, update the graphs
  if(memory.bootUpCount %10 == 0) {
    sensorData.updateData(sensors.getTemperature(), sensors.getHumidity(), sensors.getPressure());
    memory.saveSensorData(sensorData.sensorData);
  }

  printSensorData();

  display.printUI();

  display.printTemperature(sensors.getTemperature());
  display.printHumidity(sensors.getHumidity());
  display.printPressure(sensors.getPressure());
  display.printTemperatureGraph(sensorData.sensorData.temperature);
  display.printPressureGraph(sensorData.sensorData.pressure);
  display.printHumidityGraph(sensorData.sensorData.humidity);
  display.printWeatherIcon(forecast.id);

  display.update();

  memory.incrementBootupCount();
  sleep();
}

void loop() {

}

void printSensorData() {
    Serial.println("Sensor Data:");
    for (int i = 0; i < 24; ++i) {
        Serial.print("Index ");
        Serial.print(i);
        Serial.print(": Temp=");
        Serial.print(sensorData.sensorData.temperature[i], 1);
        Serial.print(", Humidity=");
        Serial.print(sensorData.sensorData.humidity[i], 1);
        Serial.print(", Pressure=");
        Serial.println(sensorData.sensorData.pressure[i], 1);
    }
    Serial.println();
}

void sleep() {
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * 1000000);
  esp_deep_sleep_start();
}