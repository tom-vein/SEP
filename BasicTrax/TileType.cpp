#include "TileType.h"

std::vector<TileType> TileType::tile_types_(6);

TileType::TileType(Shape shape, Color top_color) : shape_(shape),
  top_color_(top_color)
{
}
Shape TileType::getShape() const;
Color TileType::getTopColor() const;
Color TileType::getBottomColor() const;
Color TileType::getRightColor() const;
Color TileType::getLeftColor() const;
void TileType::initTileTypes();
const TileType& TileType::getTileType(Shape shape, Color top_color);
