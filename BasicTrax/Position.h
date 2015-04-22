//------------------------------------------------------------------------------
// Position.h
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#ifndef POSITION_H
#define POSITION_H

#include <string>
#include <sstream>

class Position
{
private:
  int x_;
  int y_;
public:
  Position(int x, int y);

  int getX() const;
  int getY() const;

  std::string toString() const;

  bool operator==(const Position& other) const;
  bool operator!=(const Position& other) const;
};

#endif // POSITION_H
