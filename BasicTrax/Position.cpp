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

bool Position::parse(const std::string& input)
{
  char none;
  std::istringstream istr;
  istr.str(input);

  istr >> none;

  if(none != '(')
  {
    x_ = 0;
    y_ = 0;
    return false;
  }

  istr >> x_;

  istr >> none;

  if(none != ',')
  {
    x_ = 0;
    y_ = 0;
    return false;
  }

  istr >> y_;

  istr >> none;

  if(none != ')')
  {
    x_ = 0;
    y_ = 0;
    return false;
  }

  istr >> none;

  if(!istr.eof())
  {
    x_ = 0;
    y_ = 0;
    return false;
  }

  return true;
}

std::string Position::toString() const
{
  std::ostringstream ostr;
  ostr << "(" << x_ << "," << y_ << ")";
  return ostr.str();
}
