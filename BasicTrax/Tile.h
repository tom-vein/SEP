#ifndef TILE_H
#define TILE_H

#include "TileType.h"
#include "Position.h"

class Tile
{
private:
  TileType type_;
  Position position_;
public:
  Tile(TileType type, Position position);
};

#endif // TILE_H
