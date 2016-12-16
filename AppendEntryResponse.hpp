#pragma once

#include "Arduino.h"
#include "ArduinoJson.h"

namespace locke {

template <size_t N>
class AppendEntryResponse {
 public:
  AppendEntryResponse(StaticJsonBuffer<N>&, const char*);
  AppendEntryResponse(StaticJsonBuffer<N>&, bool, uint32_t);
  bool success() const;
  uint32_t term() const;
  void print();
 private:
  JsonObject& _json;
};

}
