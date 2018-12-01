#pragma once

#include <Arduino.h>

#include <queue>

class Logger {

public:
  char buffer[256];
  void logBuffer(int n) { queue_.push(new String(buffer)); }
  void log(const char *str) { new String(str); }

  void enq(String *s) { queue_.push(s); }
  String *deq() {
    if (queue_.empty())
      return nullptr;
    auto ret = queue_.front();

    queue_.pop();
    return ret;
  }

  std::queue<String *> queue_;
};

extern Logger logger;
