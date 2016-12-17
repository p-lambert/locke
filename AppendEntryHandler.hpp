#pragma once

#include "RaftServer.hpp"
#include "Log.hpp"
#include "AppendEntry.hpp"

namespace locke {

class AppendEntryHandler {
 public:
  AppendEntryHandler(
      RaftServer&,
      StaticJsonBuffer<MAX_JSON_SIZE>& buff,
      const AppendEntry&);

  void process();
 private:
  void update_server();
  void try_append();
  void append();
  void reply(bool);
  RaftServer& server;
  StaticJsonBuffer<MAX_JSON_SIZE>& buff;
  const AppendEntry& req;
};

}
