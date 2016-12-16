#include "Constants.hpp"
#include "AppendEntryResponse.hpp"

using namespace locke;

template <size_t N>
AppendEntryResponse<N>::AppendEntryResponse
(StaticJsonBuffer<N>& json, const char* msg) : _json(json.parseObject(msg)) {}

template <size_t N>
AppendEntryResponse<N>::AppendEntryResponse
(StaticJsonBuffer<N>& json, bool success, uint32_t term) :
    _json(json.createObject())
{
  _json["success"] = success;
  _json["term"] =  term;
}

template <size_t N>
uint32_t AppendEntryResponse<N>::term() const
{
  return _json["term"];
}

template <size_t N>
bool AppendEntryResponse<N>::success() const
{
  return _json["success"];
}

template <size_t N>
void AppendEntryResponse<N>::print()
{
  _json.printTo(Serial);
}

template class AppendEntryResponse<MAX_JSON_SIZE>;
