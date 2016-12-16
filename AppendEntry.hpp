#pragma once

#include "Arduino.h"
#include "ArduinoJson.h"
#include "Log.hpp"
#include "Server.hpp"

namespace locke {

template <size_t N>
class AppendEntry {
 public:
  AppendEntry(StaticJsonBuffer<N>&, const char*);

  AppendEntry(
      StaticJsonBuffer<N>&,
      const Server&,
      const LogEntry&,
      const LogEntry&);

  uint32_t term() const;
  char leader() const;
  uint32_t prev_index() const;
  uint32_t prev_term() const;
  const char* entry() const;
  bool isHeartbeat() const;
  void print();
 private:
  JsonObject& _json;
};

}
