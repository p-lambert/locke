#pragma once

#include "Constants.hpp"
#include "Arduino.h"

namespace locke {

class Configuration;

typedef struct {
  uint32_t idx;
  uint32_t term;
  char value[MAX_LOG_VALUE_SIZE];
} LogEntry;

class Log {
 public:
  void append(LogEntry*);
  bool fetch(LogEntry*, uint32_t);
  void prepare(LogEntry*, uint32_t, uint32_t, const char*);
  bool is_empty() const;
  bool exists(uint32_t) const;
  void truncate(uint32_t);
  uint32_t _tail;
 private:
  uint32_t _update_tail();

  friend Configuration;
};

}
