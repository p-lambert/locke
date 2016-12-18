#pragma once

#include "Arduino.h"
#include "ArduinoJson.h"
#include "Log.hpp"
#include "RaftServer.hpp"

namespace locke {

class RequestVote {
 public:
  RequestVote(JsonObject&);

  RequestVote(
      StaticJsonBuffer<JSON_LARGE>&,
      const RaftServer&,
      const Log::Entry&);

  uint32_t term() const;
  char candidate() const;
  uint32_t last_index() const;
  uint32_t last_term() const;
  void print();
 private:
  JsonObject& _json;
};

}
