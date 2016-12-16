#include "Constants.hpp"
#include "AppendEntryResponse.hpp"

using namespace locke;

AppendEntryResponse::AppendEntryResponse
(StaticJsonBuffer<MAX_JSON_SIZE>& json, const char* msg)
    : _json(json.parseObject(msg)) {}

AppendEntryResponse::AppendEntryResponse
(StaticJsonBuffer<MAX_JSON_SIZE>& json, bool success, uint32_t term) :
    _json(json.createObject())
{
  _json["success"] = success;
  _json["term"] =  term;
}

uint32_t AppendEntryResponse::term() const
{
  return _json["term"];
}

bool AppendEntryResponse::success() const
{
  return _json["success"];
}

void AppendEntryResponse::print()
{
  _json.printTo(Serial);
}
