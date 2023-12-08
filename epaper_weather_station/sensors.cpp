
#include "sensors.h"

Sensors::Sensors(int dht22Pin) : dht22(dht22Pin) {
  // Additional initialization code for other sensors if needed
}

float Sensors::getTemperature(){
  return temperature;
}

float Sensors::getHumidity(){
  return humidity;
}

float Sensors::getPressure(){
  return pressure;
}

void Sensors::begin(){
  bmp.begin();
}

void Sensors::readSensors() {
  temperature = dht22.getTemperature();
  humidity = dht22.getHumidity();
  pressure = bmp.readPressure()/97.5;
}