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
    case Shape::CURVE_TOP_LEFT_CORNER:
      return (TileType::top_color_ = Color::WHITE) ? Color::WHITE : Color::RED;
    case Shape::CURVE_TOP_RIGHT_CORNER:
      return (TileType::top_color_ = Color::WHITE) ? Color::WHITE : Color::RED;
  }
}

Color TileType::getRightColor() const
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

Color TileType::getLeftColor() const
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

void TileType::initTileTypes()
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

const TileType& TileType::getTileType(Shape shape, Color top_color)
{

}

