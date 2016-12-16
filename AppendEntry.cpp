#include "Constants.hpp"
#include "AppendEntry.hpp"

using namespace locke;

AppendEntry::AppendEntry(StaticJsonBuffer<MAX_JSON_SIZE>& json, const char* msg) :
    _json(json.parseObject(msg)) {}

AppendEntry::AppendEntry
(StaticJsonBuffer<MAX_JSON_SIZE>& json,
 const Server& server,
 const LogEntry& entry,
 const LogEntry& previous_entry) : _json(json.createObject())
{
  _json["term"] = server.current_term;
  _json["leader"] = (uint8_t)server.name;
  _json["prev_index"] = previous_entry.idx;
  _json["prev_term"] = previous_entry.term;
  _json["entry"] = entry.value;
}

uint32_t AppendEntry::term() const
{
  return _json["term"];
}

char AppendEntry::leader() const
{
  return (uint8_t)_json["leader"];
}

uint32_t AppendEntry::prev_index() const
{
  return _json["prev_index"];
}

uint32_t AppendEntry::prev_term() const
{
  return _json["prev_term"];
}

const char* AppendEntry::entry() const
{
  return _json["entry"];
}

bool AppendEntry::isHeartbeat() const
{
  return !_json.containsKey("entry") || strlen(_json["entry"]) == 0;
}

void AppendEntry::print()
{
  _json.printTo(Serial);
}
