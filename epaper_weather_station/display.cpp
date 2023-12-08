#include "display.h"
#include "icons.h"

Display::Display() {
  
}

void Display::begin(){
  display.begin();
  display.clearDisplay();  
}

void Display::printFrame(){
  display.drawRect(0, 0, 600, 448, INKPLATE_BLACK);
  display.drawRect(1, 1, 598, 446, INKPLATE_BLACK);
  display.drawRect(2, 2, 596, 444, INKPLATE_BLACK);
  display.drawRect(3, 3, 594, 442, INKPLATE_BLACK);
}

void Display::printSmallFrame(int x, int y)
{
   display.drawRoundRect(x, y, 243, 173, 20, INKPLATE_BLACK);
   display.drawRoundRect(x + 1, y + 1, 241, 171, 20, INKPLATE_BLACK);
}

void Display::printTitle(int x, int y, String text)
{
  display.setTextColor(INKPLATE_BLACK);
  display.setTextSize(3);
  display.setCursor(x, y);
  display.print(text);
}

void Display::printTemperature(float temperature) {
  char buffer[6];
  dtostrf(temperature, 4, 1, buffer);
  display.setTextColor(INKPLATE_RED);
  display.setTextSize(5);
  display.setCursor(340, 95);
  display.print(buffer);
  display.print(" ");
  display.print((char)247);
  display.print("C");
}

void Display::printTemperatureGraph(float *data){

  int x = 340;
  int y = 190;

  float minValue;
  float maxValue;
  for (int i = 0; i < 24; ++i) {
    if(data[i] !=0){
      minValue = min(minValue, data[i]);
      maxValue = max(maxValue, data[i]);
    }
  }

  // Calculate the width of each data point on the x-axis
  float xStep = 230 / 24;
  float yScale = 40.0 / (maxValue - minValue);

  for (int i = 0; i < 23; ++i) {
      int x1 = x + i * xStep;
      int y1 = y - int((data[i] - minValue) * yScale);
      int x2 = x + (i + 1) * xStep;
      int y2 = y - int((data[i + 1] - minValue) * yScale);
      display.drawLine(x1, y1, x2, y2, INKPLATE_RED);
      display.drawLine(x1, y1 + 1, x2, y2 + 1, INKPLATE_RED);
      display.drawLine(x1, y1 + 2, x2, y2 + 2, INKPLATE_RED);
  }
}

void Display::printHumidity(float humidity) {
  char buffer[6];
  dtostrf(humidity, 4, 1, buffer);
  display.setTextColor(INKPLATE_BLUE);
  display.setTextSize(5);
  display.setCursor(350, 302);
  display.print(buffer);
  display.print(" ");
  display.print("%");
}

void Display::printPressure(float pressure) {
  char buffer[6];
  dtostrf(pressure, 5, 1, buffer);
  display.setTextColor(INKPLATE_GREEN);
  display.setTextSize(4);
  display.setCursor(55, 302);
  display.print(buffer);
  display.print(" mb");
}

void Display::update() {
  display.display();
}

void Display::printUI() {
  printFrame();
  printSmallFrame(38, 34);
  printSmallFrame(319, 34);
  printSmallFrame(38, 241);
  printSmallFrame(319, 241);
  printTitle(88, 50, "FORECAST");
  printTitle(344, 50, "TEMPERATURE");
  printTitle(90, 257, "PRESSURE");
  printTitle(375, 257, "HUMIDITY");
}

void Display::printHumidityGraph(float *data) {
  int x = 340;
  int y = 410;
  float barWidth = 180 / 24.0;

  for (int i = 0; i < 24; ++i) {
    if (data[i] != 0) {
      float barHeight = 55 * (data[i] / 100.0); // Scale the height to fit within 100
      int rectX = x + i * (barWidth + 1); // Add 1 pixel for spacing
      int rectY = y - barHeight;
      int rectWidth = barWidth;
      int rectHeight = barHeight;

      display.fillRect(rectX, rectY, rectWidth, rectHeight, INKPLATE_BLUE);
    }
  }
}

void Display::printPressureGraph(float *data) {
  int x = 60;
  int y = 410;
  float barWidth = 180 / 24.0;

  for (int i = 0; i < 24; ++i) {
    if (data[i] != 0) {
      float barHeight = 55 * ((data[i] - 970) / 50.0); // Scale the height to fit within 55
      int rectX = x + i * (barWidth + 1); // Add 1 pixel for spacing
      int rectY = y - barHeight;
      int rectWidth = barWidth;
      int rectHeight = barHeight;

      display.fillRect(rectX, rectY, rectWidth, rectHeight, INKPLATE_GREEN);
    }
  }
}

void Display::printWeatherIcon(int id){

switch(id)
 {
  case 800: drawClearWeather(); break;
  case 801: drawFewClouds(); break;
  case 802: drawFewClouds(); break;
  case 803: drawCloud(); break;
  case 804: drawCloud(); break;

  case 200: drawThunderstorm(); break;
  case 201: drawThunderstorm(); break;
  case 202: drawThunderstorm(); break;
  case 210: drawThunderstorm(); break;
  case 211: drawThunderstorm(); break;
  case 212: drawThunderstorm(); break;
  case 221: drawThunderstorm(); break;
  case 230: drawThunderstorm(); break;
  case 231: drawThunderstorm(); break;
  case 232: drawThunderstorm(); break;

  case 300: drawLightRain(); break;
  case 301: drawLightRain(); break;
  case 302: drawLightRain(); break;
  case 310: drawLightRain(); break;
  case 311: drawLightRain(); break;
  case 312: drawLightRain(); break;
  case 313: drawLightRain(); break;
  case 314: drawLightRain(); break;
  case 321: drawLightRain(); break;

  case 500: drawLightRainWithSun(); break;
  case 501: drawLightRainWithSun(); break;
  case 502: drawLightRainWithSun(); break;
  case 503: drawLightRainWithSun(); break;
  case 504: drawLightRainWithSun(); break;
  case 511: drawLightRain(); break;
  case 520: drawHeavyRain(); break;
  case 521: drawHeavyRain(); break;
  case 522: drawHeavyRain(); break;
  case 531: drawHeavyRain(); break;

  case 600: drawLightSnowfall(); break;
  case 601: drawHeavySnowfall(); break;
  case 602: drawHeavySnowfall(); break;
  case 611: drawLightSnowfall(); break;
  case 612: drawLightSnowfall(); break;
  case 615: drawLightSnowfall(); break;
  case 616: drawLightSnowfall(); break;
  case 620: drawLightSnowfall(); break;
  case 621: drawHeavySnowfall(); break;
  case 622: drawHeavySnowfall(); break;

  case 701: drawFog(); break;
  case 711: drawFog(); break;
  case 721: drawFog(); break;
  case 731: drawFog(); break;
  case 741: drawFog(); break;
  case 751: drawFog(); break;
  case 761: drawFog(); break;
  case 762: drawFog(); break;
  case 771: drawFog(); break;
  case 781: drawFog(); break;

  default:break; 
 }
}

void Display::drawClearWeather(){
  display.fillCircle(155, 140, 45, INKPLATE_ORANGE);
}

void Display::drawFewClouds(){

  display.drawBitmap(100, 90, cloud, 110, 110, INKPLATE_BLUE);
  display.drawBitmap(100, 90, sun, 110, 110, INKPLATE_ORANGE);
}

void Display::drawCloud() {
    display.drawBitmap(100, 70, cloud, 110, 110, INKPLATE_BLUE);
}

void Display::drawThunderstorm() {
  display.drawBitmap(100, 80, thunderstorm, 110, 110, INKPLATE_BLUE);
  display.drawBitmap(100, 80, thunder, 110, 110, INKPLATE_ORANGE);
}

void Display::drawLightRain() {
  display.drawBitmap(100, 90, light_rain, 110, 110, INKPLATE_BLUE);
}

void Display::drawHeavyRain() {
  display.drawBitmap(100, 84, rain, 110, 110, INKPLATE_BLUE);
}

void Display::drawLightSnowfall() {
  display.drawBitmap(100, 84, snowfall, 110, 110, INKPLATE_BLUE);
}

void Display::drawHeavySnowfall() {
  display.drawBitmap(100, 80, heavy_snowfall, 110, 110, INKPLATE_BLUE);
}

void Display::drawLightRainWithSun() {
  display.drawBitmap(100, 84, sun_light_rain, 110, 110, INKPLATE_ORANGE);
  display.drawBitmap(100, 84, light_rain_with_sun, 110, 110, INKPLATE_BLUE);
}

void Display::drawFog() {
  display.drawBitmap(100, 84, fog, 110, 110, INKPLATE_BLUE);
}
