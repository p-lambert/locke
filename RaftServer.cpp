#include "Constants.hpp"
#include "RaftServer.hpp"
#include "Configuration.hpp"
#include "Log.hpp"

using namespace locke;

RaftServer::RaftServer(char name) :
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
  set_status(Follower);
  Log::setup();
}

void RaftServer::save()
{
  Configuration::save(*this);
}

void RaftServer::restore()
{
  Configuration::restore(*this);
}
