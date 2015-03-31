#ifndef TILETYPE_H
#define TILETYPE_H

#include "Shape.h"
#include "Color.h"
#include <vector>

class TileType
{
private:
  Shape shape_;
  Color top_color_;
  static std::vector<TileType> tile_types_;
public:
  TileType(Shape shape, Color top_color);
  Shape getShape() const;
  Color getTopColor() const;
  Color getBottomColor() const;
  Color getRightColor() const;
  Color getLeftColor() const;
  static void initTileTypes();
  static const TileType& getTileType(Shape shape, Color top_color);
};

#endif // TILETYPE_H
