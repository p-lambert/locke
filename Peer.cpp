#include "Constants.hpp"
#include "Peer.hpp"

using namespace locke;

Peer::Peer(char _name, IPAddress& _ip) : name(_name), ip(_ip) {}

bool Peer::will_timeout_soon()
{
  return (millis() - last_heartbeat) > ELECTION_TIMEOUT/2;
}
