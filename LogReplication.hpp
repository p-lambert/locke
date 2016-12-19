#pragma once

#include "RaftServer.hpp"
#include "Peer.hpp"
#include "SyncRequest.hpp"

namespace locke {

class LogReplication {
 public:
  LogReplication(RaftServer&);
  void execute();
 private:
  void update_commit_index();
  Peer* outdated_peer();
  Peer* expiring_peer();
  void send_heartbeat(Peer*);
  void send_append_entry(Peer*);
  void process_result(Peer*, SyncRequest::Result*);
  RaftServer& server;
};

}
