#include "_Server.h"
#include "Configuration.h"
#include "Database.h"
#include "Log.h"

using namespace locke;

Configuration::Configuration(Server& server, Log& log) :
    _server(server),
    _log(log) {}

void Configuration::save()
{
  _ConfigurationRecord config{_server.current_term, _server.voted_for, _log._tail};
  Database::set(&config, SERVER_CFG_FILE, 0, sizeof(_ConfigurationRecord));
}

void Configuration::restore()
{
  _ConfigurationRecord config{INIT_CFG_TERM, INIT_CFG_VOTE, INIT_CFG_TAIL};
  Database::get(&config, SERVER_CFG_FILE, 0, sizeof(_ConfigurationRecord));

  _server.current_term = config.current_term;
  _server.voted_for = config.voted_for;
  _log._tail = config.log_tail;
}
