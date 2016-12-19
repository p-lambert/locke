#pragma once

#include "Arduino.h"
#include "ArduinoJson.h"
#include "Log.hpp"
#include "RaftServer.hpp"

namespace locke {

class AppendEntry {
 public:
  AppendEntry(JsonObject&);
  AppendEntry(JsonObject&, const RaftServer&);

  AppendEntry(
      JsonObject&,
      const RaftServer&,
      const Log::Entry&,
      const Log::Entry&);

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
