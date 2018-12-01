#pragma once

struct SerialCli {
  SerialCli(Stream &stream) : stream_(stream) {}
  void processLine() {
    if (line_ == "open") {
      doorOpener.activate();
      stream_.println("Door opened");
    } else if (line_ == "help") {
      stream_.println("Commands:\n"
                      "  open");
    } else
      Serial.println("Processing line: " + line_);
  }
  void loop() {
    while (stream_.available()) {
      auto ch = stream_.read();
      Serial.print(char(ch));
      if (ch == '\n' || ch == '\r') {
        if (line_.length())
          processLine();
        line_.remove(0);
      } else {
        line_ += char(ch);
      }
    }
  }

  Stream &stream_;
  String line_;
} cli{Serial};
