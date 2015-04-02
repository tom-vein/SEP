#include "TileType.h"

std::vector<TileTypeLib::TileType> TileTypeLib::TileType::tile_types_(6);

TileTypeLib::TileType::TileType(Shape shape, Color top_color) : shape_(shape),
  top_color_(top_color)
{
}

TileTypeLib::Shape TileTypeLib::TileType::getShape() const
{
  return shape_;
}

TileTypeLib::Color TileTypeLib::TileType::getTopColor() const
{
  return top_color_;
}

TileTypeLib::Color TileTypeLib::TileType::getBottomColor() const
{
  switch(shape_)
  {
    case Shape::CROSS:
      return (TileType::top_color_ = Color::WHITE) ? Color::WHITE : Color::RED;
    case Shape::CURVE_TOP_LEFT_CORNER:
      return (TileType::top_color_ = Color::WHITE) ? Color::WHITE : Color::RED;
    case Shape::CURVE_TOP_RIGHT_CORNER:
      return (TileType::top_color_ = Color::WHITE) ? Color::WHITE : Color::RED;
  }
}

TileTypeLib::Color TileTypeLib::TileType::getRightColor() const
{
  switch(shape_)
  {
    case Shape::CROSS:
      return (TileType::top_color_ = Color::WHITE) ? Color::RED : Color::WHITE;
    case Shape::CURVE_TOP_LEFT_CORNER:
      return (TileType::top_color_ = Color::WHITE) ? Color::RED : Color::WHITE;
    case Shape::CURVE_TOP_RIGHT_CORNER:
      return (TileType::top_color_ = Color::WHITE) ? Color::WHITE : Color::RED;
  }
}

TileTypeLib::Color TileTypeLib::TileType::getLeftColor() const
{
  switch(shape_)
  {
    case Shape::CROSS:
      return (TileType::top_color_ = Color::WHITE) ? Color::RED : Color::WHITE;
    case Shape::CURVE_TOP_LEFT_CORNER:
      return (TileType::top_color_ = Color::WHITE) ? Color::WHITE : Color::RED;
    case Shape::CURVE_TOP_RIGHT_CORNER:
      return (TileType::top_color_ = Color::WHITE) ? Color::RED : Color::WHITE;
  }
}

void TileTypeLib::TileType::initTileTypes()
{
  TileType cross_top_white(Shape::CROSS, Color::WHITE);
  TileType cross_top_red(Shape::CROSS, Color::RED);
  TileType curve_top_left_corner_top_white(Shape::CURVE_TOP_LEFT_CORNER,
                                           Color::WHITE);
  TileType curve_top_left_corner_top_red(Shape::CURVE_TOP_LEFT_CORNER,
                                         Color::RED);
  TileType curve_top_right_corner_top_white(Shape::CURVE_TOP_RIGHT_CORNER,
                                            Color::WHITE);
  TileType curve_top_right_corner_top_red(Shape::CURVE_TOP_RIGHT_CORNER,
                                          Color::RED);
  tile_types_.push_back(cross_top_white);
  tile_types_.push_back((cross_top_red));
  tile_types_.push_back(curve_top_left_corner_top_white);
  tile_types_.push_back(curve_top_left_corner_top_red);
  tile_types_.push_back(curve_top_right_corner_top_white);
  tile_types_.push_back(curve_top_right_corner_top_red);
}

const TileTypeLib::TileType& TileTypeLib::TileType::getTileType(Shape shape,
                                                                Color top_color)
{   
 for(TileType& tile_type : tile_types_)
 {
    if(tile_type.getTopColor() == top_color && tile_type.getShape() == shape)
      return TileType;
 }
 return nullptr;
}
