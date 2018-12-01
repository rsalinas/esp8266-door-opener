#pragma once

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

struct WebService {
  WebService() {
    server.on("/", HTTP_GET,
              [this]() { server.send(200, "text/html", mainPage(false)); });
    server.on("/cmd/ping",
              [this]() { server.send(200, "text/plain", F("pong!")); });
    server.on("/open", HTTP_POST, [this]() {
      if (!server.authenticate(WWW_USER, WWW_PASSWD)) {
        return server.requestAuthentication();
      }
      doorOpener.activate();
      server.send(200, "text/html", mainPage(true));
    });
  }
  void begin() { server.begin(); }
  String mainPage(bool done) {
    return String(F(" \
                  <html> \
                  <form action=\"/open\" method=POST> \
            <input type=submit style=\"display: inline-block; width:100%; height:100%; border:none\" value=\"")) +
           (done ? "Open again" : "Open") + "\"> \
            </form> \
            </html>";
  }

  void loop() { server.handleClient(); }

  ESP8266WebServer server{81};
};
