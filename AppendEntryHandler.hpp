#pragma once

#include "RaftServer.hpp"
#include "Log.hpp"
#include "AppendEntry.hpp"

namespace locke {

class AppendEntryHandler {
 public:
  AppendEntryHandler(
      RaftServer&,
      Log&,
      StaticJsonBuffer<MAX_JSON_SIZE>& buff,
      const AppendEntry&);

  void process();
 private:
  void process_heartbeat();
  void try_append();
  void append();
  void reply(bool);
  RaftServer& server;
  Log& log;
  StaticJsonBuffer<MAX_JSON_SIZE>& buff;
  const AppendEntry& req;
};

}
