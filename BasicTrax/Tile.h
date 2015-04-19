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
  TileTypeLib::Color getColorAtEdge(TileTypeLib::Edge edge)  {return type_.getColorAtEdge(edge);}

};

#endif // TILE_H
