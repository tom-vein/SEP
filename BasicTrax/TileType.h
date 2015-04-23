//------------------------------------------------------------------------------
// TileType.h
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#ifndef TILETYPE_H
#define TILETYPE_H

#include <vector>
#include <exception>
#include "Color.h"

namespace TileTypeLib
{
  //----------------------------------------------------------------------------
  // Shape Class
  // list of Enums to distinguish different Tile Type Shapes
  //
  enum class Shape : char
  {
    NONE = 0,
    CROSS,
    CURVE_TOP_LEFT_CORNER,
    CURVE_TOP_RIGHT_CORNER,
  };

  //----------------------------------------------------------------------------
  // Edge Class
  // list of Enums to define all Edges of a Tile
  //
  enum class Edge
  {
    NONE,
    BOTTOM,
    TOP,
    LEFT,
    RIGHT,
  };

  //----------------------------------------------------------------------------
  // method used for retrieving the opposite edge
  // e.g. Edge::LEFT --> Edge::Right
  // @param edge Edge of which the opposite should be returned
  // @return Opposite edge of given edge
  //
  Edge getOppositeEdge(Edge edge);

  //----------------------------------------------------------------------------
  // Class Tile Type, used for encapsulating the shape and the top color
  // of a tile.
  class TileType
  {
  private:

    //--------------------------------------------------------------------------
    // Shape of the tile
    //
    Shape shape_;

    //--------------------------------------------------------------------------
    // Color at the top edge of the tile
    //
    Color top_color_;

    //--------------------------------------------------------------------------
    // vector with all known tiletypes
    //
    static std::vector<TileType> tile_types_;

    //--------------------------------------------------------------------------
    // Constructor
    //
    TileType(Shape shape, Color top_color);

  public:

    //--------------------------------------------------------------------------
    // Getter Methods
    //
    Shape getShape() const;
    Color getColorAtEdge(Edge edge);

    //--------------------------------------------------------------------------
    // method used before using this class to initialize all known tile types
    //
    static void initTileTypes();

    //--------------------------------------------------------------------------
    // method used for retrieving a tiletype
    // @param shape Shape of the tile
    // @param top_color color at top edge of the tile
    // @return reference to the tiletype associated with this params
    //
    static const TileType& getTileType(Shape shape, Color top_color);

    //--------------------------------------------------------------------------
    // method used for retrieving a tile type, when
    // not the shape and top color, but the color of all edges are known
    // @param left_edge_color Color of left edge
    // @param top_edge_color Color of top edge
    // @param right_edge_color Color of right edge
    // @param bottom_edge_color of bottom edge
    //
    static const TileType& getTileType(Color left_edge_color,
                                       Color top_edge_color,
                                       Color right_edge_color,
                                       Color bottom_edge_color);

    //--------------------------------------------------------------------------
    // getter method used for retrieving all known tile types
    //
    static const std::vector<TileType>& getAllTileTypes() {return tile_types_;}
  };

}

#endif // TILETYPE_H
