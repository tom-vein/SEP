#include "TileType.h"
#include "Exceptions.h"

std::vector<TileTypeLib::TileType> TileTypeLib::TileType::tile_types_;

TileTypeLib::TileType::TileType(Shape shape, Color top_color) : shape_(shape),
  top_color_(top_color)
{
  //TODO add colors
  //TODO finish implementation
}

TileTypeLib::Shape TileTypeLib::TileType::getShape() const
{
  return shape_;
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
    if(tile_type.getColorAtEdge(Edge::TOP) == top_color && tile_type.getShape() == shape)
      return tile_type;
  }

  throw std::exception(); //Create better exception
}

TileTypeLib::Color TileTypeLib::TileType::getColorAtEdge(Edge edge) const
{
  switch(edge)
  {
    case TileTypeLib::Edge::TOP: return top_color_;
    case TileTypeLib::Edge::BOTTOM: return bottom_color_;
    case TileTypeLib::Edge::LEFT: return left_color_;
    case TileTypeLib::Edge::RIGHT: return right_color_;
  default: throw(MessageException("No such edge"));
  }
}
