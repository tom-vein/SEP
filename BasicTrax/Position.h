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

//------------------------------------------------------------------------------
// Class Position representing a 2-D position
//
class Position
{
private:
  //----------------------------------------------------------------------------
  // X-Coordinate
  //
  int x_;

  //----------------------------------------------------------------------------
  // Y-Coordinates
  //
  int y_;

public:

  //----------------------------------------------------------------------------
  // Constructor
  //
  Position(int x, int y);

  //----------------------------------------------------------------------------
  // Getter
  //
  int getX() const;
  int getY() const;

  //----------------------------------------------------------------------------
  // Method prooves if the other Position has the same x *and* y coordinate
  //
  bool operator==(const Position& other) const
  {
    return (x_ == other.x_ && y_ == other.y_) ? true : false;
  }

  //----------------------------------------------------------------------------
  // Method checks if the other Position has a different x *or* y coordinate
  //
  bool operator!=(const Position& other) const
  {
    return (x_!= other.x_ || y_ != other.y_) ? true : false;
  }

  std::string toString() const;
};

#endif // POSITION_H
