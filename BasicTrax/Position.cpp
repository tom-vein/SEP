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
std::string Position::toString() const
{
  std::ostringstream stream;
      stream << "(" << x_ << "," << y_ << ")";
      return stream.str();
}
