#include "TileType.h"

std::vector<TileType> TileType::tile_types_(6);

TileType::TileType(Shape shape, Color top_color) : shape_(shape),
  top_color_(top_color)
{
}

Shape TileType::getShape() const
{
  return shape_;
}

Color TileType::getTopColor() const
{
  return top_color_;
}

Color TileType::getBottomColor() const
{
  switch(shape_)
  {
    case Shape::CROSS:
      return (TileType::top_color_ = Color::WHITE) ? Color::WHITE : Color::RED;
  }
}

Color TileType::getRightColor() const
{
}

Color TileType::getLeftColor() const
{
}

void TileType::initTileTypes()
{
  //erzeugt die 6 arten der tiles (vector hinzufügen)
}

const TileType& TileType::getTileType(Shape shape, Color top_color)
{
  //dementsprechenden tile aus dem vector zurückgeben
}

