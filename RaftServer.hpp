#pragma once

#include "Arduino.h"

namespace locke {

enum State {
  Follower,
  Candidate,
  Leader
};

class Log;
class Configuration;

class RaftServer {
 public:
  RaftServer(Log*, char);
  void set_status(State);
  void setup();
  void save();
  void restore();
  uint32_t current_term;
  char voted_for;
  char leader;
  const char name;
  Log* _log;
 private:
  State _status;

  friend Configuration;
};

}
