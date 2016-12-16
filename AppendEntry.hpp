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
  AppendEntry(StaticJsonBuffer<N>&, const Server&, const LogEntry&);
  uint32_t term();
  char leader();
  uint32_t prev_index();
  uint32_t leader_commit();
  const char* entry();
  void print();

 private:
  JsonObject& _json;
};

}
