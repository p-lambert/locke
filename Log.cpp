#include "Constants.hpp"
#include "Log.hpp"
#include "Database.hpp"

using namespace locke;

void Log::append(LogEntry* entry)
{
  uint32_t entry_pos = _update_tail();
  Database::set(entry, LOG_FILE_NAME, entry_pos, sizeof(LogEntry));
}

bool Log::fetch(LogEntry* entry, uint32_t idx)
{
  if (!exists(idx)) return false;

  uint32_t entry_pos = (idx - 1) * sizeof(LogEntry);
  Database::get(entry, LOG_FILE_NAME, entry_pos, sizeof(LogEntry));

  return true;
}

void Log::prepare
(LogEntry* entry, uint32_t idx, uint32_t term, const char* value)
{
  entry->idx = idx;
  entry->term = term;

  if (strlen(value) <= MAX_LOG_VALUE_SIZE) {
    strcpy((char *)&entry->value, value);
  }
}

bool Log::exists(uint32_t idx) const
{
  return idx <= (_tail / sizeof(LogEntry));
}

void Log::truncate(uint32_t idx)
{
  if (!exists(idx)) return;

  _tail = (idx - 1) * sizeof(LogEntry);
}

bool Log::is_empty() const
{
  return _tail == 0;
}

void Log::setup()
{
  if (!is_empty()) return;

  LogEntry sentinel_entry;
  prepare(&sentinel_entry, 1, 1, "");
  append(&sentinel_entry);
}

uint32_t Log::_update_tail()
{
  uint32_t previous = _tail;
  _tail += sizeof(LogEntry);

  return previous;
}
