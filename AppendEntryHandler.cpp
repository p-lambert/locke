#include "AppendEntryHandler.hpp"
#include "AppendEntryResponse.hpp"

using namespace locke;

AppendEntryHandler::AppendEntryHandler
(RaftServer& server, const AppendEntry& req) : server(server), req(req) {}

void AppendEntryHandler::process()
{
  if (req.term() < server.current_term) {
    reply(false);
    return;
  }

  update_server();

  if (req.isHeartbeat()) {
    reply(true);
    return;
  }

  try_append();
}

void AppendEntryHandler::update_server()
{
  server.current_term = req.term();
  server.leader = req.leader();
  server.save();
}

void AppendEntryHandler::try_append()
{
  Log::Entry prev;
  bool prev_found = Log::fetch(&prev, req.prev_index());

  if (!prev_found) {
    reply(false);
    return;
  }

  if (prev.term != req.prev_term() || prev.idx != req.prev_index()) {
    Log::truncate(prev.idx);
    reply(false);
    return;
  }

  append();
}

void AppendEntryHandler::append()
{
  uint32_t idx = req.prev_index() + 1;

  Log::Entry new_entry;
  Log::truncate(idx);
  Log::prepare(&new_entry, idx, req.term(), req.entry());
  Log::append(&new_entry);
  server.save();

  reply(true);
}

void AppendEntryHandler::reply(bool success)
{
  StaticJsonBuffer<JSON_SMALL> buff;
  AppendEntryResponse response(buff, success, server.current_term);
  response.print();
}
