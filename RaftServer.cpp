#include "Constants.hpp"
#include "RaftServer.hpp"
#include "Configuration.hpp"
#include "Log.hpp"

using namespace locke;

RaftServer::RaftServer(Log* log, char name) :
    _log(log),
    current_term(INITIAL_TERM),
    name(name),
    voted_for(NOBODY_YET) {}

void RaftServer::set_status(State status)
{
  _status = status;
}

void RaftServer::setup()
{
  restore();
  _log->setup();
  set_status(Follower);
}

void RaftServer::save()
{
  Configuration config(*this, *_log);
  config.save();
}

void RaftServer::restore()
{
  Configuration config(*this, *_log);
  config.restore();
}
