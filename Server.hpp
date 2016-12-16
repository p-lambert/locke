#pragma once

#include "Arduino.h"

namespace locke {

enum State {
  Unknown,
  Follower,
  Candidate,
  Leader
};

class Log;
class Configuration;

class Server {
 public:
  Server(Log*, char);
  void set_status(State);
  void setup();
  void save();
  void restore();
  uint32_t current_term;
  char voted_for;
  const char name;
 private:
  State _status;
  Log* _log;

  friend Configuration;
};

}