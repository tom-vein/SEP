//------------------------------------------------------------------------------
// TileType.cpp
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#include "TileType.h"
#include "Exceptions.h"

std::vector<TileTypeLib::TileType> TileTypeLib::TileType::tile_types_;

//------------------------------------------------------------------------------
TileTypeLib::Edge TileTypeLib::getOppositeEdge(Edge edge)
{
  switch(edge)
  {
    case Edge::BOTTOM: return Edge::TOP;
    case Edge::TOP: return Edge::BOTTOM;
    case Edge::LEFT: return Edge::RIGHT;
    case Edge::RIGHT: return Edge::LEFT;
    case Edge::NONE: break;
  }

  return Edge::NONE;
}

//------------------------------------------------------------------------------
TileTypeLib::TileType::TileType(Shape shape, Color top_color) : shape_(shape),
  top_color_(top_color)
{

}

//------------------------------------------------------------------------------
TileTypeLib::Shape TileTypeLib::TileType::getShape() const
{
  return shape_;
}

//------------------------------------------------------------------------------
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
  tile_types_.push_back(cross_top_red);
  tile_types_.push_back(curve_top_left_corner_top_white);
  tile_types_.push_back(curve_top_left_corner_top_red);
  tile_types_.push_back(curve_top_right_corner_top_white);
  tile_types_.push_back(curve_top_right_corner_top_red);
}

//------------------------------------------------------------------------------
const TileTypeLib::TileType& TileTypeLib::TileType::getTileType(Shape shape,
                                                                Color top_color)
{   
  for(TileType& tile_type : tile_types_)
  {
    if(tile_type.getColorAtEdge(Edge::TOP) == top_color &&
       tile_type.getShape() == shape)
      return tile_type;
  }

  throw std::exception(); //Create better exception
}

//------------------------------------------------------------------------------
const TileTypeLib::TileType& TileTypeLib::TileType::getTileType(
    Color left_edge_color, Color top_edge_color,
    Color right_edge_color, Color bottom_edge_color)
{
  for(TileType& tile_type : tile_types_)
  {
    if(tile_type.getColorAtEdge(Edge::LEFT) == left_edge_color &&
       tile_type.getColorAtEdge(Edge::TOP) == top_edge_color &&
       tile_type.getColorAtEdge(Edge::RIGHT) == right_edge_color &&
       tile_type.getColorAtEdge(Edge::BOTTOM) == bottom_edge_color)
      return tile_type;

  }
  throw(MessageException("No such tiletype"));
}

//------------------------------------------------------------------------------
Color TileTypeLib::TileType::getColorAtEdge(Edge edge) const
{
  switch(edge)
  {
    case TileTypeLib::Edge::TOP:
    {
      return top_color_;
    }

    case TileTypeLib::Edge::BOTTOM:
    {
      if(shape_ == TileTypeLib::Shape::CROSS)
        return top_color_;
      else if(top_color_ == Color::RED)
        return Color::WHITE;
      else
        return Color::RED;
    }
    case TileTypeLib::Edge::LEFT:
    {
      if(shape_ == TileTypeLib::Shape::CROSS ||
         shape_ == TileTypeLib::Shape::CURVE_TOP_RIGHT_CORNER)
      {
        if(top_color_ == Color::RED)
          return Color::WHITE;
        else
          return Color::RED;
      }
      else
        return top_color_;
    }
    case TileTypeLib::Edge::RIGHT:
    {
      if(shape_ == TileTypeLib::Shape::CROSS ||
         shape_ == TileTypeLib::Shape::CURVE_TOP_LEFT_CORNER)
      {
        if(top_color_ == Color::RED)
          return Color::WHITE;
        else
          return Color::RED;
      }
      else
        return top_color_;
    }
  default: throw(MessageException("No such edge"));
  }
}
