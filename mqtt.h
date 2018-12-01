#pragma once

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DoorOpener.h"

//static const char* mqtt_server = "raspberrypi3";
#define mqtt_server "raspberrypi3"

struct MqttService {
	MqttService(WiFiClient& espClient) : client(espClient) {
		
	}
	void mqttReconnect();
	void begin() {
			client.setServer(mqtt_server, 1883);
		client.setCallback([this](char* topic, uint8_t* payload, unsigned int length) {
			Serial.print("Message arrived [");
		Serial.print(topic);
		Serial.print("] ");
		for (int i = 0; i < length; i++) {
			Serial.print((char)payload[i]);
		}
		Serial.println();

		if ((char)payload[0] == '1') {
			doorOpener.activate();
			client.publish("Salinas/opener/ack", "1");
		}
			});
		pingTicker.attach<MqttService*>(60.0, [](MqttService* self) {
			self->client.publish("Salinas/uptime", String(millis()).c_str());
		}, this);

	}
	void loop() {
		if (!client.connected()) {
			mqttReconnect();
		}	
		client.loop();
	}
		PubSubClient client;
private:

	Ticker pingTicker;
};

extern MqttService mqttService;
