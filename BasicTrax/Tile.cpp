//------------------------------------------------------------------------------
// Tile.cpp
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#include "Tile.h"

//------------------------------------------------------------------------------
TileTypeLib::Shape Tile::getShape() const
{
  return type_.getShape();
}
