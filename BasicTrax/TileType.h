#ifndef TILETYPE_H
#define TILETYPE_H

#include <vector>
#include <exception>

namespace TileTypeLib
{

  enum class Color
  {
    NO_COLOR,
    WHITE,
    RED
  };

  enum class Shape
  {
    CROSS,
    CURVE_TOP_LEFT_CORNER,
    CURVE_TOP_RIGHT_CORNER,
  };

  enum class Edge
  {
    BOTTOM,
    TOP,
    LEFT,
    RIGHT,
  };

  class TileType
  {
  private:
    Shape shape_;
    Color top_color_;
    static std::vector<TileType> tile_types_;
    TileType(Shape shape, Color top_color);
  public:
    Shape getShape() const;
    Color getColorAtEdge(Edge edge) const;
    static void initTileTypes();
    static const TileType& getTileType(Shape shape, Color top_color);
  };

}

#endif // TILETYPE_H
