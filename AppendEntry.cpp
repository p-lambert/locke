#include "Constants.hpp"
#include "AppendEntry.hpp"
#include "RPC.hpp"

using namespace locke;

AppendEntry::AppendEntry(JsonObject& json) : json(json) {}

AppendEntry::AppendEntry(JsonObject& json, const RaftServer& svr) : json(json)
{
  json[RPC_TYPE] = (uint8_t)RPC::AppendEntry;
  json[RPC_TERM] = svr.current_term;
}

AppendEntry::AppendEntry
(JsonObject& json,
 const RaftServer& server,
 const Log::Entry& entry,
 const Log::Entry& previous_entry) : json(json)
{

  json[RPC_TYPE] = (uint8_t)RPC::AppendEntry;
  json[RPC_TERM] = server.current_term;
  json[RPC_LEADER] = (uint8_t)server.name;
  json[RPC_PREV_IDX] = previous_entry.idx;
  json[RPC_PREV_TERM] = previous_entry.term;
  json[RPC_VALUE] = entry.value;
}

uint32_t AppendEntry::term() const
{
  return json[RPC_TERM];
}

char AppendEntry::leader() const
{
  return (uint8_t)json[RPC_LEADER];
}

uint32_t AppendEntry::prev_index() const
{
  return json[RPC_PREV_IDX];
}

uint32_t AppendEntry::prev_term() const
{
  return json[RPC_PREV_TERM];
}

const char* AppendEntry::entry() const
{
  return json[RPC_VALUE];
}

bool AppendEntry::isHeartbeat() const
{
  return !json.containsKey(RPC_VALUE) || strlen(json[RPC_VALUE]) == 0;
}

void AppendEntry::print()
{
  json.printTo(Serial);
}
