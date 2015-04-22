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

class Tile;

using TilePtr = std::shared_ptr<Tile>;


class Tile
{
private:
  TileTypeLib::TileType type_;
  Position position_;
public:
  Tile(const TileTypeLib::TileType& type,
       const Position& position) : type_(type), position_(position) {}

  TilePtr getConnectedTileAtPosition(TileTypeLib::Edge edge);
  TilePtr getConnectedTileByLine(TilePtr requester);

  const Position& getPosition() const {return position_;}
  Color getColorAtEdge(TileTypeLib::Edge edge)
        { return type_.getColorAtEdge(edge); }
  TileTypeLib::Shape getShape() const;

};

#endif // TILE_H
