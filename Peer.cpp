#include "Constants.hpp"
#include "Peer.hpp"

using namespace locke;

Peer::Peer(char _name, IPAddress& _ip) : name(_name), ip(_ip)
{
  match_index = 1;
}

bool Peer::will_timeout_soon()
{
  return (millis() - last_heartbeat) > ELECTION_TIMEOUT/2;
}

void Peer::setup(uint32_t idx)
{
  vote = Election::Vote::Unknown;
  next_index = idx + 1;
}

bool Peer::pending_vote()
{
  vote == Election::Vote::Unknown;
}

bool Peer::enabled()
{
  return millis() > retry_after;
}

void Peer::retry_later()
{
  retry_after = millis() + RETRY_AFTER;
}

void Peer::touch()
{
  last_heartbeat = millis();
}
