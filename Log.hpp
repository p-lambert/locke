#pragma once

#include "Constants.hpp"
#include "Arduino.h"

namespace locke {

class Log {
 public:

  typedef struct {
    uint32_t idx;
    uint32_t term;
    char value[MAX_LOG_VALUE_SIZE];
  } Entry;

  static void append(Entry*);
  static bool fetch(Entry*, uint32_t);
  static void prepare(Entry*, uint32_t, uint32_t, const char*);
  static bool is_empty();
  static bool exists(uint32_t);
  static void truncate(uint32_t);
  static void setup();
  static uint32_t tail;

 private:
  static uint32_t update_tail();
};

}
