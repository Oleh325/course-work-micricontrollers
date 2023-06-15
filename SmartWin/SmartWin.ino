#include <DHT11.h>
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

float desiredTemp = 24.0;
int seconds = 0;
bool isOpen = false;

void IRAM_ATTR TimerHandler()
{
  seconds++;

  Serial.println("in timer 1s");

  if (seconds == 5) {
    float temperatureInside = sensorInside.readTemperature();
    float temperatureOutside = sensorOutside.readTemperature();

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

    Serial.println(isOpen);
    Serial.println(temperatureInside);
    Serial.println(temperatureOutside);

    seconds = 0;
  }
}

void setup() {

  Serial.begin(9600);

  pinMode(D7, OUTPUT);

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
}