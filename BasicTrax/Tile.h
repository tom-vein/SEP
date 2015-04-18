#ifndef TILE_H
#define TILE_H

#include <memory>

#include "TileType.h"
#include "Position.h"

class Tile;

typedef std::shared_ptr<Tile> TilePtr;


class Tile
{
private:
  TileTypeLib::TileType type_;
  Position position_;
public:
  Tile(const TileTypeLib::TileType& type,
       const Position& position);

  //TODO: Add implementation
  Tile(const TileTypeLib::Color& color_bottom, const TileTypeLib::Color& color_left,
       const TileTypeLib::Color& color_top, const TileTypeLib::Color& color_right);

  TilePtr getConnectedTileAtPosition(TileTypeLib::Edge edge);
  TilePtr getConnectedTileByLine(TilePtr requester);

  const Position& getPosition() const {return position_;}
  TileTypeLib::Color getColorAtEdge(TileTypeLib::Edge edge)  {return type_.getColorAtEdge(edge);}

};

#endif // TILE_H
