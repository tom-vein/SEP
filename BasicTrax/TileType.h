#ifndef TILETYPE_H
#define TILETYPE_H

#include <vector>

namespace TileTypeLib
{

  enum class Color
  {
    WHITE,
    RED
  };

  enum class Shape
  {
    CROSS,
    CURVE_TOP_LEFT_CORNER,
    CURVE_TOP_RIGHT_CORNER,
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
    Color getTopColor() const;
    Color getBottomColor() const;
    Color getRightColor() const;
    Color getLeftColor() const;
    static void initTileTypes();
    static const TileType& getTileType(Shape shape, Color top_color);
  };

}

#endif // TILETYPE_H
