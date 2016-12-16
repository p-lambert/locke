#include "_Server.h"
#include "Configuration.h"

using namespace locke;

locke::Server::Server(Log* log, char name) :
    _log(log),
    name(name),
    voted_for(NOBODY_YET) {}

void locke::Server::set_status(State status)
{
  _status = status;
}

void locke::Server::setup()
{
  restore();
  set_status(Follower);
}

void locke::Server::save()
{
  Configuration config(*this, *_log);
  config.save();
}

void locke::Server::restore()
{
  Configuration config(*this, *_log);
  config.restore();
}
