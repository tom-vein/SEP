#include "Tile.h"

Tile::Tile(std::shared_ptr<TileType>& type, Position& position) :
  type_(std::move(type)), position_(position)
{
}
