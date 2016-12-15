#include "Arduino.h"

namespace locke {

  class Database {
 public:
    int static get(void*, char*, uint32_t, int);
    int static set(void*, char*, uint32_t, int);
  };

}
