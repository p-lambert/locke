#include "Constants.hpp"
#include "RequestVote.hpp"
#include "RPC.hpp"

using namespace locke;

RequestVote::RequestVote(JsonObject& json) : _json(json) {}

RequestVote::RequestVote
(StaticJsonBuffer<JSON_LARGE>& json,
 const RaftServer& server,
 const Log::Entry& last_entry) : _json(json.createObject())
{
  _json[RPC_TYPE] = (uint8_t)RPC::RequestVote;
  _json[RPC_TERM] = server.current_term;
  _json[RPC_LEADER] = (uint8_t)server.name;
  _json[RPC_LAST_IDX] = last_entry.idx;
  _json[RPC_LAST_TERM] = last_entry.term;
}

uint32_t RequestVote::term() const
{
  return _json[RPC_TERM];
}

char RequestVote::candidate() const
{
  return (uint8_t)_json[RPC_CANDIDATE];
}

uint32_t RequestVote::last_index() const
{
  return _json[RPC_LAST_IDX];
}

uint32_t RequestVote::last_term() const
{
  return _json[RPC_LAST_TERM];
}

void RequestVote::print()
{
  _json.printTo(Serial);
}
