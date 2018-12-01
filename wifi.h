#pragma once

#include <ESP8266WiFi.h>

struct WifiService {
  void begin() {
    Serial.print("Connecting to SSID: ");
    Serial.println(WIFI_SSID);
    WiFi.begin();
    // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.print(("WiFi connected. IP: "));
    Serial.println(WiFi.localIP());

    if (!MDNS.begin("dooropener")) {
      Serial.println(("Error setting up MDNS responder!"));
    }
    MDNS.addService("http", "tcp", 80);
  }
  WiFiClient espClient;
};
