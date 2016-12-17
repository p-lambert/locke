#pragma once

#include "Arduino.h"
#include "RaftServer.hpp"

namespace locke {

class RaftServer;

typedef struct {
  uint32_t current_term;
  char voted_for;
  uint32_t log_tail;
} _ConfigurationRecord;

class Configuration {
 public:
  Configuration(RaftServer&);
  void restore();
  void save();
 private:
  RaftServer& _server;
};

}
