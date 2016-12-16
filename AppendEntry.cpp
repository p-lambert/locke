#include "AppendEntry.hpp"
#include "Server.hpp"

using namespace locke;

template <size_t N>
AppendEntry<N>::AppendEntry(StaticJsonBuffer<N>& json, const char* msg)
{
  _json = json.parseObject(msg);
}

template <size_t N>
AppendEntry<N>::AppendEntry
(StaticJsonBuffer<N>& json, const Server& server, const LogEntry& entry)
{
  _json = json.createObject();

  _json["term"] = server.current_term;
  _json["leader"] = server.name;
  _json["prev_index"] = entry.idx - 1;
  _json["entry"] = entry.value;
}

template <size_t N>
uint32_t AppendEntry<N>::term()
{
  return _json["term"];
}

template <size_t N>
char AppendEntry<N>::leader()
{
  return _json["leader"][0];
}

template <size_t N>
uint32_t AppendEntry<N>::prev_index()
{
  return _json["prev_index"];
}

template <size_t N>
uint32_t AppendEntry<N>::leader_commit()
{
  return _json["leader_commit"];
}

template <size_t N>
const char* AppendEntry<N>::entry()
{
  return _json["entry"];
}

template <size_t N>
void AppendEntry<N>::print()
{
  _json.printTo(Serial);
}
