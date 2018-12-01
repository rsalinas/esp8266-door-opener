#pragma once

#include <Arduino.h>
#include <ArduinoOTA.h>

struct OtaService {

  void begin() {
    static int otaTotal = 0;
    ArduinoOTA.setPassword(OTA_PASSWORD);
    ArduinoOTA.begin();
    ArduinoOTA.onError([](ota_error_t err) {
      Serial.println("OTA error");
#ifdef USE_MQTT
      // client.publish("Salinas/OTA", "error");
#endif
    });
    ArduinoOTA.onStart([]() { Serial.println("OTA starts"); });
    ArduinoOTA.onEnd([]() {
      Serial.println("OTA ended, I will reboot now");
      // set system in a safe state (disable relays for example)
    });
    ArduinoOTA.onProgress([&](unsigned int done, unsigned int total) {
      Serial.print("OTA progress: ");
      Serial.print(done);
      Serial.print("/");
      Serial.println(total);
      otaTotal = total;
    });
  }
  void loop() { ArduinoOTA.handle(); }
};
