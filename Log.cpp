#include "Log.h"
#include "SD.h"

using namespace locke;

void Log::append(LogEntry* entry)
{
  File f = SD.open(LOG_FILE_NAME, O_WRITE | O_CREAT);
  uint32_t entry_pos = _update_tail();

  f.seek(entry_pos);
  f.write((const uint8_t *)entry, sizeof(LogEntry));
  f.close();
}

bool Log::fetch(LogEntry* entry, uint32_t _idx)
{
  uint32_t idx = _idx - 1;
  uint32_t entry_pos = idx * sizeof(LogEntry);

  if (entry_pos > _tail) {
    return false;
  }

  File f = SD.open(LOG_FILE_NAME, O_READ);
  f.seek(entry_pos);
  f.read(entry, sizeof(LogEntry));
  f.close();

  return true;
}

void Log::prepare(LogEntry* entry, uint32_t idx, uint32_t term, char* value)
{
  entry->idx = idx;
  entry->term = term;

  if (strlen(value) <= MAX_LOG_VALUE_SIZE) {
    strcpy((char *)&entry->value, value);
  }
}

uint32_t Log::_update_tail()
{
  uint32_t previous = _tail;
  _tail += sizeof(LogEntry);

  return previous;
}
