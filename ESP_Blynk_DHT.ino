#define BLYNK_TEMPLATE_ID "TMPL2bkkrV9nR"
#define BLYNK_TEMPLATE_NAME "DHT"
#define BLYNK_AUTH_TOKEN "8FXQbxp3eeZKrh8TCq4YLi1rT1xBRNff"

#ifdef ESP32
  #include <WiFi.h>
  #include <BlynkSimpleEsp32.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <BlynkSimpleEsp8266.h>
#else
  #error "Unsupported board! Use ESP32 or ESP8266."
#endif
#include "DHT.h"

// Wi-Fi credentials
#define WIFI_SSID             "2001"
#define WIFI_PASS             "19821968"

// DHT Sensor
#define DHT_PIN               25        // GPIO25   (Change it in case of ESP8266)
#define DHT_TYPE              DHT22
DHT dht(DHT_PIN, DHT_TYPE);

// Virtual pins in Blynk app
#define TEMP_VPIN   V0
#define HUM_VPIN    V1

BlynkTimer timer;         // to run a function every period of time

void sendSensorData()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed
  if (isnan(temperature) || isnan(humidity)) {
    return;
  }

  // Send data to Blynk app
  Blynk.virtualWrite(TEMP_VPIN, temperature);
  Blynk.virtualWrite(HUM_VPIN, humidity);
}

void setup()
{
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  timer.setInterval(2000L, sendSensorData);  // every 2 sec
}

void loop()
{
  Blynk.run();
  timer.run();
}