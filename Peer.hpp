#pragma once

#include "Election.hpp"
#include "Ethernet.h"
#include "Election.hpp"

namespace locke {

class Peer {
 public:
  Peer(char, IPAddress&);
  Election::Vote vote;
  bool will_timeout_soon();
  bool vote_pending();
  uint32_t last_heartbeat;
  uint32_t next_index;
  char name;
  IPAddress& ip;
};

}
