#pragma once

#include "Arduino.h"
#include "ArduinoJson.h"

namespace locke {

class AppendEntryResponse {
 public:
  AppendEntryResponse(StaticJsonBuffer<MAX_JSON_SIZE>&, const char*);
  AppendEntryResponse(StaticJsonBuffer<MAX_JSON_SIZE>&, bool, uint32_t);
  bool success() const;
  uint32_t term() const;
  void print();
 private:
  JsonObject& _json;
};

}
