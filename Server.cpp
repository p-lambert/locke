#include "_Server.h"

using namespace locke;

locke::Server::Server(IPAddress* ip, char name) : ip(ip), _name(name) {}

void locke::Server::set_status(State status)
{
  _status = status;
}

void locke::Server::load_state()
{
  PersistentState::get(*this, &current_term, &voted_for);
}

void locke::Server::save_state()
{
  PersistentState::set(*this, current_term, voted_for);
}

char locke::Server::get_name() const
{
  return _name;
}
