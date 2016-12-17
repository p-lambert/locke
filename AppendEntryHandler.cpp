#include "AppendEntryHandler.hpp"
#include "AppendEntryResponse.hpp"

using namespace locke;

AppendEntryHandler::AppendEntryHandler
(RaftServer& server,
 Log& log,
 StaticJsonBuffer<MAX_JSON_SIZE>& buff,
 const AppendEntry& req) :
    server(server),
    log(log),
    buff(buff),
    req(req) {}

void AppendEntryHandler::process()
{
  if (req.term() < server.current_term) {
    reply(false);
    return;
  }

  if (req.isHeartbeat()) {
    process_heartbeat();
    return;
  }

  try_append();
}

void AppendEntryHandler::process_heartbeat()
{
  // Update timeout
  server.current_term = req.term();
  server.leader = req.leader();
  server.save();

  reply(true);
}

void AppendEntryHandler::try_append()
{
  LogEntry prev;
  bool prev_found = log.fetch(&prev, req.prev_index());

  if (!prev_found) {
    reply(false);
    return;
  }

  if (prev.term != req.prev_term() || prev.idx != req.prev_index()) {
    log.truncate(prev.idx);
    reply(false);
    return;
  }

  append();
}

void AppendEntryHandler::append()
{
  uint32_t idx = req.prev_index() + 1;
  LogEntry new_entry;

  log.truncate(idx);
  log.prepare(&new_entry, idx, req.term(), req.entry());
  log.append(&new_entry);
  server.save();

  reply(true);
}

void AppendEntryHandler::reply(bool success)
{
  AppendEntryResponse response(buff, success, server.current_term);
  response.print();
}
