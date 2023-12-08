class ForecastManager {

  public:
    ForecastManager();
    void begin(char *ssid, char *pass);
    bool getForecast(char *id, char *apiKey);
    int id;
    
  private:

};