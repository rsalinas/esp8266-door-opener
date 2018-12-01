#include <Arduino.h>

#include "config.h" // contains the secrets, see config.h.templ

#include <Ticker.h>
#include <list>

extern "C" {
#include "user_interface.h"
}

#include "DoorOpener.h"
#include "Logger.h"
#include "SerialCli.h"
#include "Web.h"

#include "wifi.h"
WifiService wifiService;

#ifdef USE_MQTT
#include "mqtt.h"
MqttService mqttService{wifiService.espClient};
#endif
const int HEARTBEAT_LED = LED_BUILTIN;

#include "Heartbeat.h"
#include "Web.h"
#include "ota.h"

WebService webService;
Heartbeat heartbeat{HEARTBEAT_LED, []() {
#ifdef USE_MQTT
                      return mqttService.client.connected() != 0;
#endif
                      return true;
                    }};
OtaService otaService;

void setup() {
  Serial.begin(115200);
  otaService.begin();
  wifiService.begin();
#ifdef USE_MQTT
  mqttService.begin();
#endif
  Serial.print("booted in ");
  Serial.println(millis());

  webService.begin();
#if SHOW_FREERAM
  static Ticker everySecond;
  everySecond.attach(1, []() {
    logger.logBuffer(snprintf(logger.buffer, sizeof logger.buffer,
                              "Free RAM: %d", system_get_free_heap_size()));
  });
#endif
}

void setup_wifi() {}

void loop() {
  otaService.loop();
#ifdef USE_MQTT
  mqttService.loop();
#endif
  webService.loop();
  cli.loop();
  yield();
  auto s = logger.deq();
  if (s) {
    Serial.print("MSG: ");
    Serial.println(*s);
    delete s;
  }
}
