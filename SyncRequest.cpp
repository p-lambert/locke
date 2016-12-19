#include "SyncRequest.hpp"
#include "ArduinoJson.h"
#include "Response.hpp"

using namespace locke;

bool SyncRequest::perform(IPAddress& ip, char* msg, Result* res)
{
  EthernetClient client;
  StaticJsonBuffer<JSON_SMALL> json_buff;
  char buff[RESPONSE_BUFFER];
  uint8_t pos = 0;

  if (!client.connect(ip, RAFT_PORT)) {
    return false;
  }

  client.println(msg);

  while (client.connected() && pos < RESPONSE_BUFFER) {
    if (!client.available()) continue;

    char c = client.read();
    buff[pos++] = c;

    if (c == RPC_DELIMITER) {
      buff[pos] = '\0';
      break;
    }
  }

  client.stop();

  Response response(json_buff, buff);
  *res->success = response.success();
  *res->term = response.term();

  return true;
}
