#include "Constants.hpp"
#include "AppendEntry.hpp"
#include "RPC.hpp"

using namespace locke;

AppendEntry::AppendEntry
(StaticJsonBuffer<JSON_LARGE>& json, char msg[REQUEST_BUFFER]) :
    _json(json.parseObject(msg)) {}

AppendEntry::AppendEntry
(StaticJsonBuffer<JSON_LARGE>& json,
 const RaftServer& server,
 const Log::Entry& entry,
 const Log::Entry& previous_entry) : _json(json.createObject())
{

  _json[RPC_TYPE] = (uint8_t)RPC::AppendEntry;
  _json[RPC_TERM] = server.current_term;
  _json[RPC_LEADER] = (uint8_t)server.name;
  _json[RPC_PREV_IDX] = previous_entry.idx;
  _json[RPC_PREV_TERM] = previous_entry.term;
  _json[RPC_VALUE] = entry.value;
}

uint32_t AppendEntry::term() const
{
  return _json[RPC_TERM];
}

char AppendEntry::leader() const
{
  return (uint8_t)_json[RPC_LEADER];
}

uint32_t AppendEntry::prev_index() const
{
  return _json[RPC_PREV_IDX];
}

uint32_t AppendEntry::prev_term() const
{
  return _json[RPC_PREV_TERM];
}

const char* AppendEntry::entry() const
{
  return _json[RPC_VALUE];
}

bool AppendEntry::isHeartbeat() const
{
  return !_json.containsKey(RPC_VALUE) || strlen(_json[RPC_VALUE]) == 0;
}

void AppendEntry::print()
{
  _json.printTo(Serial);
}
