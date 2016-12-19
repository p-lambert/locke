#include "Constants.hpp"
#include "Arduino.h"
#include "Ethernet.h"

namespace locke {

namespace SyncRequest {

typedef struct {
  bool success;
  uint32_t term;
} Result;

bool perform(IPAddress&, char*, Result*);

}

}
