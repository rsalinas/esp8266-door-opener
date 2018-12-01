#include "config.h"

#ifdef USE_MQTT
#include "mqtt.h"

void MqttService::mqttReconnect() {
  // Loop until we're reconnected
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("Salinas", nullptr, nullptr, "Salinas/state", 2, 1,
                       "dead")) {
      Serial.println(F("connected"));
      client.publish("Salinas/uptime", "hello world");
      client.subscribe("Salinas/opener");

    } else {
      Serial.print(F("failed, rc="));
      Serial.print(client.state());
      Serial.println(F(" try again in 5 seconds"));
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
#endif
