#include "Constants.hpp"
#include "Log.hpp"
#include "Database.hpp"

using namespace locke;

uint32_t Log::tail = 0;

void Log::append(Entry* entry)
{
  uint32_t entry_pos = update_tail();
  Database::set(entry, LOG_FILE_NAME, entry_pos, sizeof(Entry));
}

bool Log::fetch(Entry* entry, uint32_t idx)
{
  if (!exists(idx)) return false;

  uint32_t entry_pos = (idx - 1) * sizeof(Entry);
  Database::get(entry, LOG_FILE_NAME, entry_pos, sizeof(Entry));

  return true;
}

void Log::prepare(Entry* entry, uint32_t idx, uint32_t term, const char* value)
{
  entry->idx = idx;
  entry->term = term;

  if (strlen(value) <= MAX_LOG_VALUE_SIZE) {
    strcpy((char *)&entry->value, value);
  }
}

bool Log::exists(uint32_t idx)
{
  return idx <= (tail / sizeof(Entry));
}

void Log::truncate(uint32_t idx)
{
  if (!exists(idx)) return;

  tail = (idx - 1) * sizeof(Entry);
}

bool Log::is_empty()
{
  return tail == 0;
}

void Log::setup()
{
  if (!is_empty()) return;

  Entry sentinel_entry;
  prepare(&sentinel_entry, 1, 1, "");
  append(&sentinel_entry);
}

uint32_t Log::update_tail()
{
  uint32_t previous = tail;
  tail += sizeof(Entry);

  return previous;
}
