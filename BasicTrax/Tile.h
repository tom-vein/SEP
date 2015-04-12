#ifndef TILE_H
#define TILE_H

#include <memory>

#include "TileType.h"
#include "Position.h"

class Tile
{
private:
  std::shared_ptr<TileTypeLib::TileType> type_;
  Position position_;
public:
  Tile(const std::shared_ptr<TileTypeLib::TileType>& type,
       const Position& position);

  std::shared_ptr<Tile> getConnectedTileAtPosition(TileTypeLib::Edge edge);
  std::shared_ptr<Tile> getConnectedTileByLine(std::shared_ptr<Tile> requester);

  const Position& getPosition() const {return position_;}

};

#endif // TILE_H
