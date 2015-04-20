#include "Tile.h"


TileTypeLib::Shape Tile::getShape() const
{
  return type_.getShape();
}
