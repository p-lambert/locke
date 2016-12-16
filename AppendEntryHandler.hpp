#pragma once

#include "Server.hpp"
#include "Log.hpp"
#include "AppendEntry.hpp"

namespace locke {

class AppendEntryHandler {
 public:
  AppendEntryHandler(
      Server&,
      Log&,
      StaticJsonBuffer<MAX_JSON_SIZE>& buff,
      const AppendEntry&);

  void process();
 private:
  void process_heartbeat();
  void try_append();
  void append();
  void reply(bool);
  Server& server;
  Log& log;
  StaticJsonBuffer<MAX_JSON_SIZE>& buff;
  const AppendEntry& req;
};

}
