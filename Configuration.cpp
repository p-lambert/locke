#include "Constants.hpp"
#include "RaftServer.hpp"
#include "Configuration.hpp"
#include "Database.hpp"
#include "Log.hpp"

using namespace locke;

void Configuration::save(RaftServer& server)
{
  Record cfg{server.current_term, server.voted_for, Log::tail};
  Database::set(&cfg, CFG_FILE_NAME, 0, sizeof(cfg));
}

void Configuration::restore(RaftServer& server)
{
  Record cfg;
  int result = Database::get(&cfg, CFG_FILE_NAME, 0, sizeof(cfg));

  if (result < 1) return;

  server.current_term = cfg.current_term;
  server.voted_for = cfg.voted_for;
  Log::tail = cfg.log_tail;
}
