#include "Arduino.h"

namespace locke {

  class Database {
 public:
    void static get(void*, char*, uint32_t, int);
    void static set(void*, char*, uint32_t, int);
  };

}
