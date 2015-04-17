#include "Game.h"
#include <utility>

GameLib::Game::Game(const std::array<PlayerLib::Player, 2>& players) :
  players_(players), active_player_(players_.at(0))
{

}

TilePtr GameLib::Game::getTileByPosition(const Position& position, int offset_x, int offset_y)
  throw(InvalidPositionException)
{
  Position position_to_return(position.getX() + offset_x, position.getY() + offset_y);
  for(std::vector<TilePtr>::iterator it = tiles_.begin(); it != tiles_.end(); it++)
  {
   if( (*it)->getPosition() == position_to_return)
     return *it;
  }
  throw InvalidPositionException("No Tile at this Position.", position);
}

void GameLib::Game::addTile(TilePtr to_add)
  throw(NoTilesLeftException)
{
  tiles_.push_back(to_add);
  if(tiles_.size() > 64) //TODO to static const
    throw NoTilesLeftException("Invalid move - not enough tiles left\n");
}

void GameLib::Game::removeTileAtPosition(const Position& position)
  throw(InvalidPositionException)
{
  for(std::vector<TilePtr>::iterator it = tiles_.begin(); it != tiles_.end(); it++)
  {
    if( (*it)->getPosition() == position)
    {
      tiles_.erase(it);
      return;
    }
  }
  throw(InvalidPositionException("No Tile with this position.", position));
}

void GameLib::Game::removeTile(TilePtr tile_to_remove)
{
  for(std::vector<TilePtr>::iterator it = tiles_.begin(); it != tiles_.end(); it++)
  {
    if( (*it) == tile_to_remove)
    {
      tiles_.erase(it);
      return;
    }
  }
  throw(InvalidPositionException("No Tile with this position.", tile_to_remove->getPosition()));
}

std::map<GameLib::RelativePosition, TilePtr> GameLib::Game::getTouchingTiles(const Position &position, int offset_x, int offset_y)
{
  std::map<GameLib::RelativePosition, TilePtr> touching_tiles;
  TilePtr tile;
  // Left
  if(tile = getTileByPosition(position, offset_x - 1, offset_y))
    touching_tiles.insert(std::pair<GameLib::RelativePosition, TilePtr>(GameLib::RelativePosition::LEFT, tile));
  // Top
  if(tile = getTileByPosition(position, offset_x, offset_y -1))
    touching_tiles.insert(std::pair<GameLib::RelativePosition, TilePtr>(GameLib::RelativePosition::TOP, tile));
  //Right
  if(tile = getTileByPosition(position, offset_x + 1, offset_y))
    touching_tiles.insert(std::pair<GameLib::RelativePosition, TilePtr>(GameLib::RelativePosition::RIGHT, tile));
  //Bottom
  if(tile = getTileByPosition(position, offset_x, offset_y + 1))
    touching_tiles.insert(std::pair<GameLib::RelativePosition, TilePtr>(GameLib::RelativePosition::BOTTOM, tile));
  return touching_tiles;
}
std::vector<Position> GameLib::Game::getEmptyPositionsAround(const Position& position, int offset_x, int offset_y)
{
  std::vector<Position> empty_positions;
  // Left
  if(!getTileByPosition(position, offset_x - 1, offset_y))
    empty_positions.push_back(Position(position.getX() + offset_x - 1, position.getY() + offset_y));
  // Top
  if(!getTileByPosition(position, offset_x, offset_y -1))
    empty_positions.push_back(Position(position.getX() + offset_x, position.getY() + offset_y-1));
  //Right
  if(!getTileByPosition(position, offset_x + 1, offset_y))
    empty_positions.push_back(Position(position.getX() + offset_x + 1, position.getY() + offset_y));
  //Bottom
  if(!getTileByPosition(position, offset_x, offset_y + 1))
    empty_positions.push_back(Position(position.getX() + offset_x, position.getY() + offset_y + 1));

  return empty_positions;
}
