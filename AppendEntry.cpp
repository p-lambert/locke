#include "Constants.hpp"
#include "AppendEntry.hpp"

using namespace locke;

template <size_t N>
AppendEntry<N>::AppendEntry(StaticJsonBuffer<N>& json, const char* msg) :
    _json(json.parseObject(msg)) {}

template <size_t N>
AppendEntry<N>::AppendEntry
(StaticJsonBuffer<N>& json,
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

template <size_t N>
uint32_t AppendEntry<N>::term() const
{
  return _json["term"];
}

template <size_t N>
char AppendEntry<N>::leader() const
{
  return (uint8_t)_json["leader"];
}

template <size_t N>
uint32_t AppendEntry<N>::prev_index() const
{
  return _json["prev_index"];
}

template <size_t N>
uint32_t AppendEntry<N>::prev_term() const
{
  return _json["prev_term"];
}

template <size_t N>
const char* AppendEntry<N>::entry() const
{
  return _json["entry"];
}

template <size_t N>
bool AppendEntry<N>::isHeartbeat() const
{
  return !_json.containsKey("entry") || strlen(_json["entry"]) == 0;
}

template <size_t N>
void AppendEntry<N>::print()
{
  _json.printTo(Serial);
}

template class AppendEntry<MAX_JSON_SIZE>;
