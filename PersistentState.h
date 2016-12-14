#pragma once

#include "_Server.h"
#include "SD.h"

#define state_file_name(name) {'s', '_', name, '\0'}

#define FILE_BUFF_SIZE 12

namespace locke {
  class Server;

  class PersistentState
  {
 public:
    static void get(const locke::Server&, unsigned long*, char*);
    static void set(const locke::Server&, unsigned long, char);
 private:
    static void _chomp(char *, int);
  };
}
