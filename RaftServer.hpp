#pragma once

#include "Arduino.h"

namespace locke {

enum State {
  Follower,
  Candidate,
  Leader
};

class Configuration;

class RaftServer {
 public:
  RaftServer(char);
  void set_status(State);
  void setup();
  void save();
  void restore();
  uint32_t current_term;
  char voted_for;
  char leader;
  const char name;
 private:
  State _status;

  friend Configuration;
};

}
