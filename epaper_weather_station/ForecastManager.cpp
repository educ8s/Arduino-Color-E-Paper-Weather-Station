#include "ForecastManager.h"
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

ForecastManager::ForecastManager() {
  id = 0;
}

void ForecastManager::begin(char *ssid, char *pass)
{
    // Initiating wifi, like in BasicHttpClient example
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    int cnt = 0;
    Serial.print(F("Waiting for WiFi to connect..."));
    while ((WiFi.status() != WL_CONNECTED))
    {
        Serial.print(F("."));
        delay(1000);
        ++cnt;

        if (cnt == 20)
        {
            Serial.println("Can't connect to WIFI, restarting");
            delay(100);
            ESP.restart();
        }
    }
    Serial.println(F(" connected"));
}

bool ForecastManager::getForecast(char *id, char *apiKey) {

  char *currentWeather;

   HTTPClient http;
   http.getStream().setNoDelay(true);
   http.getStream().setTimeout(1);

    // Add woeid to api call
    char url[256];
    sprintf(url, "https://api.openweathermap.org/data/2.5/forecast?id=%s&units=metric&cnt=1&APPID=%s", id, apiKey);

    http.begin(url);

    // Dynamic Json from ArduinoJson library
    DynamicJsonDocument doc(30000);

    int httpCode = http.GET();
    if (httpCode == 200)
    {
      int32_t len = http.getSize();

        if (len > 0)
        {
            // Try parsing JSON object
            DeserializationError error = deserializeJson(doc, http.getStream());

            // If an error happens print it to Serial monitor
            if (error)
            {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.c_str());
                return 0;
            }
            else
            {
                String forecastString = doc["list"][0]["weather"][0]["id"];
                int forecastInt = forecastString.toInt();
                // Assign the converted value to the id variable
                this->id = forecastInt;
            }
        }
    }            
  
  doc.clear();
  http.end();
  return 1;  
}
