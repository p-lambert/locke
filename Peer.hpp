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
  bool pending_vote();
  bool enabled();
  void retry_later();
  void reset();
  void touch();
  uint32_t last_heartbeat;
  uint32_t next_index;
  uint32_t retry_after;
  char name;
  IPAddress& ip;
};

}
