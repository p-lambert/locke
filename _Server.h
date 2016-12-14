#pragma once

#include "IPAddress.h"
#include "PersistentState.h"

namespace locke {
  enum State {
    Unknown,
    Follower,
    Candidate,
    Leader
  };

  class Server {
 public:
    Server(IPAddress*, char);
    void load_state();
    void save_state();
    void set_status(State);
    char get_name() const;
    unsigned long current_term;
    char voted_for;
    char leader;
 private:
    const char _name;
    const IPAddress* ip;
    State _status;
  };

}
