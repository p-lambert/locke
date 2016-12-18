#pragma once

#include "RaftServer.hpp"
#include "Log.hpp"
#include "RequestVote.hpp"

namespace locke {

class RequestVoteHandler {
 public:
  RequestVoteHandler(RaftServer&, const RequestVote&);
  void process();
 private:
  void reply(bool);
  RaftServer& server;
  const RequestVote& req;
};

}
