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
  return TilePtr();
}

void GameLib::Game::addTile(TilePtr to_add)
  throw(NoTilesLeftException)
{
  tiles_.push_back(to_add);
  if(tiles_.size() > MAX_OF_TILES)
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

std::map<TileTypeLib::Edge, TilePtr> GameLib::Game::getTouchingTiles(const Position &position, int offset_x, int offset_y)
{
  std::map<TileTypeLib::Edge, TilePtr> touching_tiles;
  TilePtr tile;
  // Left
  if(tile = getTileByPosition(position, offset_x - 1, offset_y))
    touching_tiles.insert(std::pair<TileTypeLib::Edge, TilePtr>(TileTypeLib::Edge::LEFT, tile));
  // Top
  if(tile = getTileByPosition(position, offset_x, offset_y -1))
    touching_tiles.insert(std::pair<TileTypeLib::Edge, TilePtr>(TileTypeLib::Edge::TOP, tile));
  //Right
  if(tile = getTileByPosition(position, offset_x + 1, offset_y))
    touching_tiles.insert(std::pair<TileTypeLib::Edge, TilePtr>(TileTypeLib::Edge::RIGHT, tile));
  //Bottom
  if(tile = getTileByPosition(position, offset_x, offset_y + 1))
    touching_tiles.insert(std::pair<TileTypeLib::Edge, TilePtr>(TileTypeLib::Edge::BOTTOM, tile));
  return touching_tiles;
}
std::map<TileTypeLib::Edge, TileTypeLib::Color> GameLib::Game::getTouchingColors(const Position &position, int offset_x, int offset_y)
{
  std::map<TileTypeLib::Edge, TileTypeLib::Color> touching_colors;
  TilePtr tile;
  //Left
  if(tile = getTileByPosition(position, offset_x - 1, offset_y))
    touching_colors.insert(std::pair<TileTypeLib::Edge, TileTypeLib::Color>(TileTypeLib::Edge::LEFT, tile->getColorAtEdge(TileTypeLib::Edge::LEFT)));
  else
    touching_colors.insert(std::pair<TileTypeLib::Edge, TileTypeLib::Color>(TileTypeLib::Edge::LEFT, TileTypeLib::Color::NO_COLOR));

  //Top
  if(tile = getTileByPosition(position, offset_x, offset_y -1))
    touching_colors.insert(std::pair<TileTypeLib::Edge, TileTypeLib::Color>(TileTypeLib::Edge::TOP, tile->getColorAtEdge(TileTypeLib::Edge::TOP)));
  else
    touching_colors.insert(std::pair<TileTypeLib::Edge, TileTypeLib::Color>(TileTypeLib::Edge::TOP, TileTypeLib::Color::NO_COLOR));

  //Right
  if(tile = getTileByPosition(position, offset_x + 1, offset_y))
    touching_colors.insert(std::pair<TileTypeLib::Edge, TileTypeLib::Color>(TileTypeLib::Edge::RIGHT, tile->getColorAtEdge(TileTypeLib::Edge::RIGHT)));
  else
    touching_colors.insert(std::pair<TileTypeLib::Edge, TileTypeLib::Color>(TileTypeLib::Edge::RIGHT, TileTypeLib::Color::NO_COLOR));

  //bottom
  if(tile = getTileByPosition(position, offset_x, offset_y + 1))
    touching_colors.insert(std::pair<TileTypeLib::Edge, TileTypeLib::Color>(TileTypeLib::Edge::BOTTOM, tile->getColorAtEdge(TileTypeLib::Edge::BOTTOM)));
  else
    touching_colors.insert(std::pair<TileTypeLib::Edge, TileTypeLib::Color>(TileTypeLib::Edge::BOTTOM, TileTypeLib::Color::NO_COLOR));
  return touching_colors;
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
