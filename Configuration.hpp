#pragma once

#include "Arduino.h"
#include "RaftServer.hpp"

namespace locke {

namespace Configuration {

typedef struct {
  uint32_t current_term;
  char voted_for;
  uint32_t log_tail;
} Record;

void restore(RaftServer&);
void save(RaftServer&);

}

}
