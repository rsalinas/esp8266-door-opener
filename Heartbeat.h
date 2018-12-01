#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>

class Heartbeat {
public:
  Heartbeat(int pin, std::function<bool(void)> cb) : pin(pin), cb_(cb) {
    pinMode(pin, OUTPUT);    // Initialize the BUILTIN_LED pin as an output
    digitalWrite(pin, HIGH); // Turn the LED off by making the voltage HI
    healthTicker.attach<Heartbeat *>(
        0.1,
        [](Heartbeat *self) {
          if (self->n++ % 20 == 0 && WiFi.status() == WL_CONNECTED &&
              self->cb_()

          ) {
            digitalWrite(self->pin,
                         LOW); // Turn the LED off by making the voltage HIGH

          } else {
            digitalWrite(
                self->pin,
                HIGH); // Turn the LED on (Note that LOW is the voltage level
          }
        },
        this);
  }

private:
  int pin;
  std::function<bool(void)> cb_;
  Ticker healthTicker;
  int n = 0;
};
