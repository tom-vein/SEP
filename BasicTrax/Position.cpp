#include "Position.h"

Position::Position(int x, int y) : x_(x), y_(y)
{
}

int Position::getX() const
{
  return x_;
}

int Position::getY() const
{
  return y_;
}

std::string Position::toString() const
{
  std::ostringstream ostr;
  ostr << "(" << x_ << "," << y_ << ")";
  return ostr.str();
}

bool Position::operator ==(const Position& other) const
{
  if(other.getX() == x_ && other.getY() == y_)
    return true;
  else
    return false;
}
bool Position::operator !=(const Position& other) const
{
  if(other.getX() != x_ || other.getY() != y_)
    return true;
  else
    return false;
}
