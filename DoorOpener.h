#pragma once

#include <Arduino.h>
#include <Ticker.h>

const int OPEN_SIGNAL_LED = 16;
const int OPENER_PIN = 5;

class DoorOpener {
public:
  DoorOpener(int relay, int led) : relay_(relay), led_(led) {
    pinMode(OPEN_SIGNAL_LED, OUTPUT);
    pinMode(OPENER_PIN, OUTPUT);
    digitalWrite(OPENER_PIN, LOW);
    digitalWrite(OPEN_SIGNAL_LED,
                 HIGH); // Turn the LED off by making the voltage HIGH
  }
  void activate() {
    Serial.println("opendoor()");
    if (led_ >= 0)
      digitalWrite(led_,
                   LOW); // Turn the LED on (Note that LOW is the voltage level
    digitalWrite(relay_, HIGH);
    relayTicker.once<DoorOpener *>(
        1.0,
        [](DoorOpener *self) {
          if (self->led_ >= 0)
            digitalWrite(self->led_,
                         HIGH); // Turn the LED off by making the voltage HIGH
          digitalWrite(self->relay_, LOW);
        },
        this);
  }

private:
  int relay_;
  int led_;
  Ticker relayTicker;
};

extern DoorOpener doorOpener;
