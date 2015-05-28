//------------------------------------------------------------------------------
// Tile.h
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#ifndef TILE_H
#define TILE_H

#include <memory>

#include "TileType.h"
#include "Position.h"

//------------------------------------------------------------------------------
// Forward declaration
//
class Tile;

using TilePtr = std::shared_ptr<Tile>;


//------------------------------------------------------------------------------
// Class represents a specific single Tile
//
class Tile
{
private:
  //----------------------------------------------------------------------------
  // tiletype of this specific tile
  //
  TileTypeLib::TileType type_;

  //----------------------------------------------------------------------------
  // Position in the gameboard of this tile
  //
  Position position_;

public:
  //----------------------------------------------------------------------------
  // constructor
  //
  Tile(const TileTypeLib::TileType& type,
       const Position& position) : type_(type), position_(position) {}

  //----------------------------------------------------------------------------
  // Getter
  //
  const Position& getPosition() const {return position_;}

  Color getColorAtEdge(TileTypeLib::Edge edge) const
  {
    return type_.getColorAtEdge(edge);
  }

  TileTypeLib::Shape getShape() const;

};

#endif // TILE_H
