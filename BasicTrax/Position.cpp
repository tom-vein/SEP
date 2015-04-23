//------------------------------------------------------------------------------
// Position.cpp
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#include "Position.h"

//------------------------------------------------------------------------------
Position::Position(int x, int y) : x_(x), y_(y)
{
}

//------------------------------------------------------------------------------
int Position::getX() const
{
  return x_;
}

//------------------------------------------------------------------------------
int Position::getY() const
{
  return y_;
}

//------------------------------------------------------------------------------
bool Position::operator ==(const Position& other) const
{
  if(other.getX() == x_ && other.getY() == y_)
    return true;
  else
    return false;
}

//------------------------------------------------------------------------------
bool Position::operator !=(const Position& other) const
{
  if(other.getX() != x_ || other.getY() != y_)
    return true;
  else
    return false;
}
