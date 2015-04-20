#ifndef TILETYPE_H
#define TILETYPE_H

#include <vector>
#include <exception>
#include "Color.h"

namespace TileTypeLib
{
  enum class Shape
  {
    CROSS,
    CURVE_TOP_LEFT_CORNER,
    CURVE_TOP_RIGHT_CORNER,
  };

  enum class Edge
  {
    NONE,
    BOTTOM,
    TOP,
    LEFT,
    RIGHT,
  };

  Edge getOppositeEdge(Edge edge);

  class TileType
  {
  private:
    Shape shape_;
    Color top_color_;
    static std::vector<TileType> tile_types_;
    TileType(Shape shape, Color top_color);

  public:
    Shape getShape() const;
    Color getColorAtEdge(Edge edge);
    static void initTileTypes();
    static const TileType& getTileType(Shape shape, Color top_color);
    static const TileType& getTileType(Color left_edge_color, Color top_edge_color,
                                       Color right_edge_color, Color bottom_edge_color);
    static const std::vector<TileType>& getAllTileTypes() {return tile_types_;}
  };

}

#endif // TILETYPE_H
