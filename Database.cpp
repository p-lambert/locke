#include "Database.h"
#include "SD.h"

using namespace locke;

int Database::get(void *record, char* file_name, uint32_t pos, int size)
{
  File f = SD.open(file_name, O_READ);
  f.seek(pos);
  int result = f.read(record, size);
  f.close();

  return result;
}

int Database::set(void *record, char* file_name, uint32_t pos, int size)
{
  File f = SD.open(file_name, O_WRITE | O_CREAT);
  f.seek(pos);
  int result = f.write((const uint8_t *)record, size);
  f.close();

  return result;
}
