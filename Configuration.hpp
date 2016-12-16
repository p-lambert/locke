#pragma once

#include "Arduino.h"
#include "Server.hpp"

namespace locke {

class Server;

typedef struct {
  uint32_t current_term;
  char voted_for;
  uint32_t log_tail;
} _ConfigurationRecord;

class Configuration {
 public:
  Configuration(Server&, Log&);
  void restore();
  void save();
 private:
  Server& _server;
  Log& _log;
};

}
