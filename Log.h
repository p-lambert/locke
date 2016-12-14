#pragma once

#include "Arduino.h"

#define MAX_LOG_VALUE_SIZE 30
#define LOG_FILE_NAME "raft_log"

namespace locke {

  typedef struct {
    uint32_t idx;
    uint32_t term;
    char value[MAX_LOG_VALUE_SIZE];
  } LogEntry;

  class Log {
 public:
    void append(LogEntry*);
    bool fetch(LogEntry*, uint32_t);
    void prepare(LogEntry*, uint32_t, uint32_t, char*);
 private:
    uint32_t _tail;
    uint32_t _update_tail();
    bool _exists(uint32_t);
  };

}
