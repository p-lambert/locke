#include "Constants.hpp"
#include "AppendEntryResponse.hpp"

using namespace locke;

AppendEntryResponse::AppendEntryResponse
(StaticJsonBuffer<JSON_SMALL>& json, const char* msg)
    : _json(json.parseObject(msg)) {}

AppendEntryResponse::AppendEntryResponse
(StaticJsonBuffer<JSON_SMALL>& json, bool success, uint32_t term) :
    _json(json.createObject())
{
  _json[AE_SUCCESS] = success;
  _json[AE_TERM] =  term;
}

uint32_t AppendEntryResponse::term() const
{
  return _json[AE_TERM];
}

bool AppendEntryResponse::success() const
{
  return _json[AE_SUCCESS];
}

void AppendEntryResponse::print()
{
  _json.printTo(Serial);
}
