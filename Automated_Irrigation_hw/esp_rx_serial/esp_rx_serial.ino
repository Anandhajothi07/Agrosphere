#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "config.h"

// Pin Definitions
#define PUMP_PIN D5  // Define pump control pin
SoftwareSerial espSerial(D2, D1); // RX (D2), TX (D1)

// Variables for sensor readings and control
float soilMoisture = 0;
float rain = 0;
bool pumpOverride = false;
unsigned long pumpOverrideEndTime = 0;
unsigned long lastWeatherCheck = 0;
const unsigned long WEATHER_CHECK_INTERVAL = 60000; // Check weather every minute

// Adafruit IO Feeds
AdafruitIO_Feed *soilMoistureFeed = io.feed("soilmoisture");
AdafruitIO_Feed *rainFeed = io.feed("rain");
AdafruitIO_Feed *pumpFeed = io.feed("pump");
AdafruitIO_Feed *locationFeed = io.feed("location");

// Weather API settings
const String CITY = "Vellore";
const String COUNTRY_CODE = "IN";
const String WEATHER_API_KEY = "ed2e0bbb458b4846a36155921232008";

// Function declarations
void handlePump(char *data);
float getWeatherData();
void controlPump();

void setup() {
  Serial.begin(115200);
  espSerial.begin(9600);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, HIGH); // Assuming active LOW pump

  // Connect to Adafruit IO
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // Set up pump control message handler
  pumpFeed->onMessage(handlePump);

  // Wait for connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
  
  // Subscribe to pump control feed
  pumpFeed->get();
}

void loop() {
  io.run();

  // Read soil moisture from Arduino Nano
  if (espSerial.available() > 0) {
    soilMoisture = espSerial.parseFloat();
    Serial.print("Soil Moisture: ");
    Serial.println(soilMoisture);
    soilMoistureFeed->save(soilMoisture);
  }

  // Check weather periodically
  if (millis() - lastWeatherCheck >= WEATHER_CHECK_INTERVAL) {
    rain = getWeatherData();
    rainFeed->save(rain);
    lastWeatherCheck = millis();
  }

  // Control pump based on conditions
  controlPump();

  // Check for pump override timeout
  if (pumpOverride && millis() > pumpOverrideEndTime) {
    pumpOverride = false;
    pumpFeed->save("OFF");
  }

  delay(2000);
}

void handlePump(AdafruitIO_Data *data) {
  Serial.print("Received pump command: ");
  Serial.println(data->value());

  if (String(data->value()) == "ON") {
    digitalWrite(PUMP_PIN, LOW);  // Turn pump on (active LOW)
    pumpOverride = true;
    pumpOverrideEndTime = millis() + 600000; // 10 minute override
  } else {
    digitalWrite(PUMP_PIN, HIGH); // Turn pump off
    pumpOverride = false;
  }
}

float getWeatherData() {
  HTTPClient http;
  String serverPath = "http://api.weatherapi.com/v1/current.json?key=" + 
                     String(WEATHER_API_KEY) + "&q=" + CITY + "&aqi=no";
  
  http.begin(serverPath);
  int httpResponseCode = http.GET();
  
  if (httpResponseCode > 0) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    
    // Get rain data
    float precipitation = doc["current"]["precip_mm"];
    
    // Update location feed
    String location = doc["location"]["name"].as<String>();
    locationFeed->save(location.c_str());
    
    http.end();
    return precipitation;
  }
  
  http.end();
  return 0.0;
}

void controlPump() {
  if (!pumpOverride) {
    if (soilMoisture < 50 && rain < 0.1) {
      digitalWrite(PUMP_PIN, LOW);  // Turn pump on
    } else if (soilMoisture >= 50 || rain >= 0.5) {
      digitalWrite(PUMP_PIN, HIGH); // Turn pump off
    }
  }
}