#include "Constants.hpp"
#include "AppendEntry.hpp"

using namespace locke;

AppendEntry::AppendEntry(StaticJsonBuffer<MAX_JSON_SIZE>& json, const char* msg) :
    _json(json.parseObject(msg)) {}

AppendEntry::AppendEntry
(StaticJsonBuffer<MAX_JSON_SIZE>& json,
 const RaftServer& server,
 const Log::Entry& entry,
 const Log::Entry& previous_entry) : _json(json.createObject())
{
  _json[AE_TERM] = server.current_term;
  _json[AE_LEADER] = (uint8_t)server.name;
  _json[AE_PREV_IDX] = previous_entry.idx;
  _json[AE_PREV_TERM] = previous_entry.term;
  _json[AE_VALUE] = entry.value;
}

uint32_t AppendEntry::term() const
{
  return _json[AE_TERM];
}

char AppendEntry::leader() const
{
  return (uint8_t)_json[AE_LEADER];
}

uint32_t AppendEntry::prev_index() const
{
  return _json[AE_PREV_IDX];
}

uint32_t AppendEntry::prev_term() const
{
  return _json[AE_PREV_TERM];
}

const char* AppendEntry::entry() const
{
  return _json[AE_VALUE];
}

bool AppendEntry::isHeartbeat() const
{
  return !_json.containsKey(AE_VALUE) || strlen(_json[AE_VALUE]) == 0;
}

void AppendEntry::print()
{
  _json.printTo(Serial);
}
