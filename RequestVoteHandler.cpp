#include "RequestVoteHandler.hpp"
#include "Response.hpp"

using namespace locke;

RequestVoteHandler::RequestVoteHandler
(RaftServer& server, const RequestVote& req) : server(server), req(req) {}

void RequestVoteHandler::process()
{
  if (req.term() < server.current_term) {
    reply(false);
    return;
  }

  if (server.voted_for != NOBODY_YET && server.voted_for != req.candidate()) {
    reply(false);
    return;
  }

  Log::Entry last_entry;
  Log::last(&last_entry);

  if (last_entry.term > req.last_term()) {
    reply(false);
    return;
  }

  if (last_entry.term == req.last_term() && last_entry.idx > req.last_index()) {
    reply(false);
    return;
  }

  server.voted_for = req.candidate();
  server.save();

  reply(true);
}

void RequestVoteHandler::reply(bool success)
{
  StaticJsonBuffer<JSON_SMALL> buff;
  uint32_t current_term = server.current_term;
  Response response(buff, success, current_term, RPC::RequestVoteResponse);
  response.print();
}
