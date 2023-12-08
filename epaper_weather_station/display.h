#include "Inkplate.h"

class Display {

public:
  Display();
  void begin();
  void update();
  void printUI();
  void printTemperature(float temperature);
  void printHumidity(float humidity);
  void printPressure(float pressure);
  void printTemperatureGraph(float data[]);
  void printHumidityGraph(float data[]);
  void printPressureGraph(float data[]);
  void printWeatherIcon(int id);

private:
  Inkplate display;
  void printFrame();
  void printSmallFrame(int x, int y);
  void printTitle(int x, int y, String text);
  void drawClearWeather();
  void drawFewClouds();
  void drawCloud();
  void drawThunderstorm();
  void drawLightRain();
  void drawHeavyRain();
  void drawLightSnowfall();
  void drawHeavySnowfall();
  void drawFog();
  void drawLightRainWithSun();
};