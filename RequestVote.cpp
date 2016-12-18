#include "Constants.hpp"
#include "RequestVote.hpp"

using namespace locke;

RequestVote::RequestVote
(StaticJsonBuffer<JSON_LARGE>& json, char msg[REQUEST_BUFFER]) :
    _json(json.parseObject(msg)) {}

RequestVote::RequestVote
(StaticJsonBuffer<JSON_LARGE>& json,
 const RaftServer& server,
 const Log::Entry& last_entry) : _json(json.createObject())
{
  _json[AE_TERM] = server.current_term;
  _json[AE_LEADER] = (uint8_t)server.name;
  _json[AE_LAST_IDX] = last_entry.idx;
  _json[AE_LAST_TERM] = last_entry.term;
}

uint32_t RequestVote::term() const
{
  return _json[AE_TERM];
}

char RequestVote::candidate() const
{
  return (uint8_t)_json[AE_CANDIDATE];
}

uint32_t RequestVote::last_index() const
{
  return _json[AE_LAST_IDX];
}

uint32_t RequestVote::last_term() const
{
  return _json[AE_LAST_TERM];
}

void RequestVote::print()
{
  _json.printTo(Serial);
}
