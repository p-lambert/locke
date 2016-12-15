#include "Database.h"
#include "SD.h"

using namespace locke;

void Database::get(void *result, char* file_name, uint32_t pos, int size)
{
  File f = SD.open(file_name, O_READ);
  f.seek(pos);
  f.read(result, size);
  f.close();
}

void Database::set(void *value, char* file_name, uint32_t pos, int size)
{
  File f = SD.open(file_name, O_WRITE | O_CREAT);
  f.seek(pos);
  f.write((const uint8_t *)value, size);
  f.close();
}
