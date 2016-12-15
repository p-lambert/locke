#pragma once

#include "Arduino.h"
#include "_Server.h"

#define SERVER_CFG_FILE "svr_cfg"

namespace locke {
  class Server;

  typedef struct {
    uint32_t current_term;
    char voted_for;
    uint32_t log_tail;
  } _ConfigurationRecord;

  class Configuration
  {
 public:
    Configuration(Server&, Log&);
    void restore();
    void save();
 private:
    Server& _server;
    Log& _log;
  };
}
