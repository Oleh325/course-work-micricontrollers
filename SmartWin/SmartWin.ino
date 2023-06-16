#include <DHT11.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "wifi_data.h"
#include "ESP8266TimerInterrupt.h"
#include "ESP8266_ISR_Timer.h"

#define USING_TIM_DIV1 true
#define USING_TIM_DIV16 false
#define USING_TIM_DIV256 false
#define TIMER_INTERVAL_MS 1000
#define D0 16
#define D1 5
#define D7 13

// Create an instance of the DHT11 class and set the digital I/O pin.
DHT11 sensorInside(D1);
DHT11 sensorOutside(D0);

ESP8266Timer ITimer;
ESP8266WiFiMulti WiFiMulti;

float desiredTemp;
float temperatureInside;
float temperatureOutside;
int seconds = 0;
bool isOpen = false;
bool gotNewInfo = false;
bool transmitData = false;

String mainURL ="http://192.168.0.102:8000/";

void IRAM_ATTR TimerHandler()
{
  seconds++;
  if (seconds == 15) {
    temperatureInside = sensorInside.readTemperature();
    temperatureOutside = sensorOutside.readTemperature();

    float tempDiff = temperatureInside - temperatureOutside;

    if (tempDiff > 0.0) {
      if (desiredTemp >= temperatureInside) {
        if (isOpen) {
          isOpen = !isOpen;
        }
      }
      else {
        if (!isOpen) {
          isOpen = !isOpen;
        }
      }
    }
    else {
      if (desiredTemp <= temperatureInside) {
        if (isOpen) {
          isOpen = !isOpen;
        }
      }
      else {
        if (!isOpen) {
          isOpen = !isOpen;
        }
      }
    }

    Serial.print("Is window open: ");
    Serial.println(isOpen);
    Serial.print("Temperature inside: ");
    Serial.println(temperatureInside);
    Serial.print("Temperature outside: ");
    Serial.println(temperatureOutside);
    
    seconds = 0;
    gotNewInfo = false;
    transmitData = true;
  }
}

void setup() {

  Serial.begin(9600);

  pinMode(D7, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SSID, WIFI_PASSWORD);

  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler))
  {
    unsigned long lastMillis = millis();
    Serial.print("Starting  ITimer OK, millis() = "); Serial.println(lastMillis);
  }
  else
    Serial.println("Can't set ITimer correctly. Select another freq. or interval");
}

void loop() {
  if (isOpen)
  {
    digitalWrite(D7, HIGH);
    delayMicroseconds(1100);
    digitalWrite(D7, LOW);
    delayMicroseconds(18900);
  }
  if (!isOpen)
  {
    digitalWrite(D7, HIGH);
    delayMicroseconds(1600);
    digitalWrite(D7, LOW);
    delayMicroseconds(18400);
  }
  if (WiFiMulti.run() == WL_CONNECTED) {
    if (!gotNewInfo) {
      WiFiClient client;
      HTTPClient http;
      Serial.println();
      Serial.print("[HTTP] begin...");
      if (http.begin(client, mainURL+"desired_temp")) {
        Serial.println("[HTTP] GET...");
        int httpCode = http.GET();
        if (httpCode > 0) {
          Serial.printf("[HTTP] GET... code: %d \n", httpCode);
          if (httpCode == HTTP_CODE_OK) {
            StaticJsonDocument<100> doc;
            String payload = http.getString();
            DeserializationError error = deserializeJson(doc, payload);
            if (error) {
              Serial.print(F("deserializeJson() failed: "));
              Serial.println(error.f_str());
              return;
            }
            desiredTemp = doc["desired_temp"];
            Serial.print("Desired temperature: ");
            Serial.println(desiredTemp);
            gotNewInfo = true;
          }
        } else {
          Serial.printf("[HTTP] GET... failed, error: %s", http.errorToString(httpCode).c_str());
        }
        http.end();
      } else {
        Serial.printf("[HTTP} Unable to connect");
      }
    }
    if (transmitData) {
      WiFiClient client;
      HTTPClient http;
      Serial.println();
      Serial.print("[HTTP] begin...");
      if (http.begin(client, mainURL+"temp_data?temp_in="+temperatureInside+"&temp_out="+temperatureOutside)) {
        Serial.println("[HTTP] POST...");
        int httpCode = http.POST("");
        if (httpCode > 0) {
          Serial.printf("[HTTP] POST... code: %d \n", httpCode);
          if (httpCode == HTTP_CODE_CREATED) {
            transmitData = false;
          }
        } else {
          Serial.printf("[HTTP] POST... failed, error: %s", http.errorToString(httpCode).c_str());
        }
        http.end();
      } else {
        Serial.printf("[HTTP} Unable to connect");
      }
    }
  }
}