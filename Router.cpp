#include "Router.hpp"
#include "AppendEntry.hpp"
#include "AppendEntryHandler.hpp"
#include "RequestVote.hpp"
#include "RequestVoteHandler.hpp"

using namespace locke;

Router::Router(EthernetServer& eth_svr, RaftServer& raft_svr) :
    eth_svr(eth_svr), raft_svr(raft_svr) {}

void Router::handle_request()
{
  EthernetClient client = eth_svr.available();

  if (!client) return;

  StaticJsonBuffer<JSON_LARGE> json_buff;
  char msg_buff[REQUEST_BUFFER];
  listen(client, msg_buff);
  JsonObject& json = json_buff.parseObject(msg_buff);
  RPC::Type rpc = rpc_type(json);

  if (rpc == RPC::AppendEntry) {
      AppendEntry append_entry(json);
      AppendEntryHandler handler(raft_svr, append_entry);
      handler.process();
  } else if (rpc == RPC::RequestVote) {
      RequestVote request_vote(json);
      RequestVoteHandler handler(raft_svr, request_vote);
      handler.process();
  } else {
      Serial.println(F("Unknown RPC type"));
  }

  client.stop();
}

void Router::listen(EthernetClient& client, char buff[REQUEST_BUFFER])
{
  uint8_t pos = 0;

  while (client.connected() && pos < REQUEST_BUFFER) {
    if(!client.available()) continue;

    char c = client.read();
    buff[pos++] = c;

    if (c == RPC_DELIMITER) {
      buff[pos] = '\0';
      break;
    }
  }
}

RPC::Type Router::rpc_type(JsonObject& json)
{
  return (uint8_t)json[RPC_TYPE];
}
