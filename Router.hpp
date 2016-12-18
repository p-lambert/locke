#pragma once

#include "Constants.hpp"
#include "RaftServer.hpp"
#include "RPC.hpp"
#include "Ethernet.h"
#include "ArduinoJson.h"

namespace locke {

class Router {
 public:
  Router(EthernetServer&, RaftServer&);
  void handle_request();
 private:
  void listen(EthernetClient&, char[REQUEST_BUFFER]);
  RPC::Type rpc_type(JsonObject&);
  EthernetServer& eth_svr;
  RaftServer& raft_svr;
};

}
