#pragma once

#include "Arduino.h"
#include "ArduinoJson.h"

namespace locke {

class AppendEntryResponse {
 public:
  AppendEntryResponse(StaticJsonBuffer<JSON_SMALL>&, const char*);
  AppendEntryResponse(StaticJsonBuffer<JSON_SMALL>&, bool, uint32_t);
  bool success() const;
  uint32_t term() const;
  void print();
 private:
  JsonObject& _json;
};

}
