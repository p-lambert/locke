#pragma once

#include "Arduino.h"
#include "ArduinoJson.h"
#include "RPC.hpp"

namespace locke {

class Response {
 public:
  Response(StaticJsonBuffer<JSON_SMALL>&, char[RESPONSE_BUFFER]);
  Response(StaticJsonBuffer<JSON_SMALL>&, bool, uint32_t, RPC::Type);
  bool success() const;
  uint32_t term() const;
  RPC::Type type() const;
  void print();
 private:
  JsonObject& _json;
};

}
