#include "Constants.hpp"
#include "Server.hpp"
#include "Configuration.hpp"
#include "Database.hpp"
#include "Log.hpp"

using namespace locke;

Configuration::Configuration(Server& server, Log& log) :
    _server(server),
    _log(log) {}

void Configuration::save()
{
  _ConfigurationRecord cfg{_server.current_term, _server.voted_for, _log._tail};
  Database::set(&cfg, CFG_FILE_NAME, 0, sizeof(cfg));
}

void Configuration::restore()
{
  _ConfigurationRecord cfg;
  int result = Database::get(&cfg, CFG_FILE_NAME, 0, sizeof(cfg));

  if (result < 1) return;

  _server.current_term = cfg.current_term;
  _server.voted_for = cfg.voted_for;
  _log._tail = cfg.log_tail;
}
