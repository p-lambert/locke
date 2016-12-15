#pragma once

#include "Arduino.h"
#include "_Server.h"

#define NOBODY_YET '\0'

#define SERVER_CFG_FILE "server_config"

#define INIT_CFG_TERM 0
#define INIT_CFG_TAIL 0
#define INIT_CFG_VOTE NOBODY_YET

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
