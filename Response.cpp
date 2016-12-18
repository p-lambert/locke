#include "Constants.hpp"
#include "Response.hpp"
#include "RPC.hpp"

using namespace locke;

Response::Response
(StaticJsonBuffer<JSON_SMALL>& json, const char* msg)
    : _json(json.parseObject(msg)) {}

Response::Response
(StaticJsonBuffer<JSON_SMALL>& json,
 bool success,
 uint32_t term,
 RPC::Type type) : _json(json.createObject())
{
  _json[RPC_TYPE] = type;
  _json[RPC_SUCCESS] = success;
  _json[RPC_TERM] =  term;
}

uint32_t Response::term() const
{
  return _json[RPC_TERM];
}

bool Response::success() const
{
  return _json[RPC_SUCCESS];
}

RPC::Type Response::type() const
{
  return (uint8_t)_json[RPC_TYPE];
}

void Response::print()
{
  _json.printTo(Serial);
}
