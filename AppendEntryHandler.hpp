#pragma once

#include "RaftServer.hpp"
#include "Log.hpp"
#include "AppendEntry.hpp"

namespace locke {

class AppendEntryHandler {
 public:
  AppendEntryHandler(RaftServer&, const AppendEntry&);
  void process();
 private:
  void update_server();
  void try_append();
  void append();
  void reply(bool);
  RaftServer& server;
  const AppendEntry& req;
};

}
