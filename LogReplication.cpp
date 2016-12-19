#include "LogReplication.hpp"
#include "AppendEntry.hpp"
#include "SyncRequest.hpp"
#include "Peer.hpp"

using namespace locke;

LogReplication::LogReplication(RaftServer& server) : server(server) {}

void LogReplication::execute()
{
  Peer* peer;
  update_commit_index();

  if (peer = expiring_peer()) {
    send_heartbeat(peer);
    return;
  }

  if (!(peer = outdated_peer())) {
    return;
  }

  send_append_entry(peer);
}

void LogReplication::update_commit_index()
{
  for (uint32_t idx = server.last_index; idx > 1; idx--) {
    uint8_t count = 1;

    for (uint8_t i = 0; i < NUM_PEERS; i++) {
      if (server.peers[i]->match_index >= idx) {
        count++;
      }
    }

    if (count >= MAJORITY) {
      server.commit_index = idx;
      break;
    }
  }
}

Peer* LogReplication::expiring_peer()
{
  for (int i = 0; i < NUM_PEERS; i++) {
    Peer* peer = server.peers[i];

    if (peer->enabled() && peer->will_timeout_soon()) {
      return peer;
    }
  }

  return nullptr;
}

Peer* LogReplication::outdated_peer()
{
  for (int i = 0; i < NUM_PEERS; i++) {
    Peer* peer = server.peers[i];

    if (peer->enabled() && peer->next_index <= server.last_index)  {
      return peer;
    }
  }

  return nullptr;
}

void LogReplication::send_heartbeat(Peer* peer)
{
  StaticJsonBuffer<JSON_LARGE> large_buff;
  JsonObject& json = large_buff.createObject();
  AppendEntry heartbeat(json, server);

  SyncRequest::Result result;

  if (!SyncRequest::perform(peer->ip, heartbeat.json, &result)) {
    peer->retry_later();
    return;
  }

  if (!result.success && result.term > server.current_term) {
    server.set_status(Follower);
    return;
  }

  peer->touch();
}

void LogReplication::send_append_entry(Peer* peer)
{
  StaticJsonBuffer<JSON_LARGE> large_buff;
  JsonObject& json = large_buff.createObject();

  Log::Entry next, prev;
  Log::fetch(&next, peer->next_index);
  Log::fetch(&prev, peer->next_index - 1);

  AppendEntry append_entry(json, server, next, prev);

  SyncRequest::Result result;

  if (!SyncRequest::perform(peer->ip, append_entry.json, &result)) {
    peer->retry_later();
    return;
  }

  process_result(peer, &result);
}

void LogReplication::process_result(Peer* peer, SyncRequest::Result* result)
{
  if (result->term > server.current_term) {
    server.current_term = result-> term;
    server.set_status(Follower);
    return;
  }

  if (!result->success) {
    peer->next_index--;
    peer->touch();
    return;
  }

  peer->match_index = peer->next_index;
  peer->next_index++;
  peer->touch();
}
