#include <Adafruit_BMP085.h>
#include <DHT22.h>

class Sensors {

public:
  Sensors(int dht22Pin);
  void begin();
  void readSensors();
  float getTemperature();
  float getHumidity();
  float getPressure();

private:
  Adafruit_BMP085 bmp;
  DHT22 dht22;
  float temperature;
  float humidity;
  float pressure;
};