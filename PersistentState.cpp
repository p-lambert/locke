#include "_Server.h"
#include "PersistentState.h"

using namespace locke;

void
PersistentState::get(const locke::Server& server, unsigned long* term, char* vote)
{
  char file_name[] = state_file_name(server.get_name());
  File f = SD.open(file_name, O_READ);
  char buff[FILE_BUFF_SIZE];
  int pos = 0;

  for(; pos < FILE_BUFF_SIZE - 1 && f.available(); pos++)
    buff[pos] = f.read();

  buff[pos] = '\0';
  _chomp(&buff[0], FILE_BUFF_SIZE);
  sscanf(buff, "%lu %c", term, vote);

  f.close();
}

void
PersistentState::set(const locke::Server& server, unsigned long term, char vote)
{
  char file_name[] = state_file_name(server.get_name());
  File f = SD.open(file_name, O_WRITE | O_CREAT | O_TRUNC);
  char buff[FILE_BUFF_SIZE];

  sprintf(buff, "%lu %c", term, vote);
  f.print(buff);
  f.close();
}

void PersistentState::_chomp(char *str, int n)
{
  while (--n >= 0) {
    if (str[n] == '\n') {
      str[n] = '\0';
      return;
    }
  }
}
