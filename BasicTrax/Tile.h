#ifndef TILE_H
#define TILE_H

#include <memory>

#include "TileType.h"
#include "Position.h"

class Tile
{
private:
  std::shared_ptr<TileTypeLib::TileType> type_;
  Position position_;
public:
  Tile(const std::shared_ptr<TileTypeLib::TileType>& type,
       const Position& position);
};

#endif // TILE_H
