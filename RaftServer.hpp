#pragma once

#include "Arduino.h"

namespace locke {

enum State {
  Follower,
  Candidate,
  Leader
};

class RaftServer {
 public:
  RaftServer(char);
  State get_status();
  void set_status(State);
  void update_election_timeout();
  bool should_become_candidate();
  void setup();
  void save();
  void restore();
  uint32_t current_term;
  char voted_for;
  char leader;
  Peer peers[NUM_PEERS];
  const char name;
 private:
  State _status;
  uint32_t _election_timeout;
};

}
