//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//


#include "Game.h"
#include <utility>
#include <algorithm>

//------------------------------------------------------------------------------
GameLib::Game::Game(const std::array<Player, 2>& players) :
  players_(players), active_player_(players_.at(0))
{

}

//------------------------------------------------------------------------------
TilePtr GameLib::Game::getTileByPosition(Position position,
                                         int offset_x, int offset_y) const
{
  position.add(offset_x, offset_y);

  std::vector<TilePtr>::const_iterator it = std::find_if(tiles_.begin(),
                                                         tiles_.end(),
                                                         [=](TilePtr tile)
  {return (tile->getPosition() == position) ? true : false;});
  if(it != tiles_.end())
    return *it;
  return nullptr;
}

//------------------------------------------------------------------------------
void GameLib::Game::addTile(TilePtr tile_to_add)
{
  if(tiles_.size() >= MAX_OF_TILES)
    throw NoTilesLeftException("Invalid move - not enough tiles left");

  tiles_.push_back(tile_to_add);
  ++num_of_placed_tiles_in_current_turn_;
}

//------------------------------------------------------------------------------
void GameLib::Game::removeTileAtPosition(const Position& position)
throw(InvalidPositionException)
{
  size_t before = tiles_.size();

  std::remove_if(tiles_.begin(), tiles_.end(), [=](TilePtr tile)
  {return (tile->getPosition() == position) ? true : false;});
  if(tiles_.size() != before)
    --num_of_placed_tiles_in_current_turn_;
  else
    throw(MessageException("No Tile with this position!"));
}

//------------------------------------------------------------------------------
void GameLib::Game::removeTile(TilePtr tile_to_remove)
{
  size_t before = tiles_.size();

  tiles_.erase(std::remove(tiles_.begin(), tiles_.end(), tile_to_remove), tiles_.end());
  if(tiles_.size() != before)
    --num_of_placed_tiles_in_current_turn_;
  else
    throw(MessageException("No such Tile!"));
}

//------------------------------------------------------------------------------
std::map<TileTypeLib::Edge, TilePtr> GameLib::Game::getTouchingTiles(
    const Position &position, Color color, int offset_x, int offset_y) const
{
  std::map<TileTypeLib::Edge, TilePtr> touching_tiles;
  TilePtr tile;

  // Left
  if((tile = getTileByPosition(position, offset_x - 1, offset_y)) &&
     (color == Color::NONE ||
      tile->getColorAtEdge(TileTypeLib::Edge::RIGHT) == color))
    touching_tiles[TileTypeLib::Edge::LEFT] = tile;

  // Top
  if((tile = getTileByPosition(position, offset_x, offset_y -1)) &&
     (color == Color::NONE ||
      tile->getColorAtEdge(TileTypeLib::Edge::BOTTOM) == color))
    touching_tiles[TileTypeLib::Edge::TOP] = tile;

  //Right
  if((tile = getTileByPosition(position, offset_x + 1, offset_y)) &&
     (color == Color::NONE ||
      tile->getColorAtEdge(TileTypeLib::Edge::LEFT) == color))
    touching_tiles[TileTypeLib::Edge::RIGHT] = tile;

  //Bottom
  if((tile = getTileByPosition(position, offset_x, offset_y + 1)) &&
     (color == Color::NONE ||
      tile->getColorAtEdge(TileTypeLib::Edge::TOP) == color))
    touching_tiles[TileTypeLib::Edge::BOTTOM] = tile;

  return touching_tiles;
}

//------------------------------------------------------------------------------
std::map<TileTypeLib::Edge, Color> GameLib::Game::getTouchingColors(
    const Position &position, int offset_x, int offset_y) const
{
  std::map<TileTypeLib::Edge, Color> touching_colors;
  TilePtr tile;
  //Left
  if((tile = getTileByPosition(position, offset_x - 1, offset_y)))
    touching_colors[TileTypeLib::Edge::LEFT] =
        tile->getColorAtEdge(TileTypeLib::Edge::RIGHT);
  else
    touching_colors[TileTypeLib::Edge::LEFT] = Color::NONE;

  //Top
  if((tile = getTileByPosition(position, offset_x, offset_y - 1)))
    touching_colors[TileTypeLib::Edge::TOP] =
        tile->getColorAtEdge(TileTypeLib::Edge::BOTTOM);
  else
    touching_colors[TileTypeLib::Edge::TOP] = Color::NONE;

  //Right
  if((tile = getTileByPosition(position, offset_x + 1, offset_y)))
    touching_colors[TileTypeLib::Edge::RIGHT] =
        tile->getColorAtEdge(TileTypeLib::Edge::LEFT);
  else
    touching_colors[TileTypeLib::Edge::RIGHT] = Color::NONE;

  //Bottom
  if((tile = getTileByPosition(position, offset_x, offset_y + 1)))
    touching_colors[TileTypeLib::Edge::BOTTOM] =
        tile->getColorAtEdge(TileTypeLib::Edge::TOP);
  else
    touching_colors[TileTypeLib::Edge::BOTTOM] = Color::NONE;

  return touching_colors;
}

//------------------------------------------------------------------------------
std::vector<Position> GameLib::Game::getEmptyPositionsAround(
    const Position& position, int offset_x, int offset_y) const
{
  std::vector<Position> empty_positions;
  // Left
  if(!getTileByPosition(position, offset_x - 1, offset_y))
    empty_positions.push_back(Position(position.getX() + offset_x - 1,
                                       position.getY() + offset_y));
  // Top
  if(!getTileByPosition(position, offset_x, offset_y - 1))
    empty_positions.push_back(Position(position.getX() + offset_x,
                                       position.getY() + offset_y - 1));
  //Right
  if(!getTileByPosition(position, offset_x + 1, offset_y))
    empty_positions.push_back(Position(position.getX() + offset_x + 1,
                                       position.getY() + offset_y));
  //Bottom
  if(!getTileByPosition(position, offset_x, offset_y + 1))
    empty_positions.push_back(Position(position.getX() + offset_x,
                                       position.getY() + offset_y + 1));

  return empty_positions;
}

bool GameLib::Game::hasEmptyPositions(Position position) const
{
  if(getTileByPosition(position, -1, 0) == nullptr ||
     getTileByPosition(position, 1, 0) == nullptr ||
     getTileByPosition(position, 0, -1) == nullptr ||
     getTileByPosition(position, 0, 1) == nullptr)
    return true;

  return false;

}

std::vector<TilePtr> GameLib::Game::getAllEdges() const
{
  std::vector<TilePtr> edges;
  for(std::vector<TilePtr>::const_iterator tiles_iterator = tiles_.begin();
      tiles_iterator != tiles_.end(); tiles_iterator++)
  {
    if(hasEmptyPositions((*tiles_iterator)->getPosition()))
      edges.push_back(*tiles_iterator);
  }
  return edges;
}

//------------------------------------------------------------------------------
std::vector<TilePtr> GameLib::Game::getLastPlacedTiles() const
{
  std::vector<TilePtr> last_placed_tiles;
  TilePtr tile;
  unsigned int pos;

  for(unsigned int i = 0; i < num_of_placed_tiles_in_current_turn_; i++)
  {
    pos = tiles_.size() - 1 - i;
    tile = tiles_.at(pos);
    last_placed_tiles.push_back(tile);
  }

  return last_placed_tiles;
}

//------------------------------------------------------------------------------
const Player& GameLib::Game::getActivePlayer() const
{
  return active_player_;
}

//------------------------------------------------------------------------------
const Player& GameLib::Game::getPausedPlayer() const
{
  if(active_player_ == players_.at(0))
    return players_.at(1);

  if(active_player_ == players_.at(1))
    return players_.at(0);

  throw MessageException("No suitable paused player found!!!");
}

//------------------------------------------------------------------------------
int GameLib::Game::getMaxXValue() const
{
  int max_x_value;

  if(tiles_.empty())
    throw NoTilesLeftException("there are no tiles");

  max_x_value = tiles_.at(0)->getPosition().getX();

  for(unsigned int tile_index = 1; tile_index < tiles_.size(); tile_index++)
  {
    TilePtr tile = tiles_.at(tile_index);

    if(tile->getPosition().getX() > max_x_value)
      max_x_value = tile->getPosition().getX();
  }

  return max_x_value;
}

//------------------------------------------------------------------------------
int GameLib::Game::getMinXValue() const
{
  int min_x_value;

  if(tiles_.empty())
    throw NoTilesLeftException("there are no tiles");

  min_x_value = tiles_.at(0)->getPosition().getX();

  for(unsigned int tiles_index = 1; tiles_index < tiles_.size(); tiles_index++)
  {
    TilePtr tile = tiles_.at(tiles_index);

    if(tile->getPosition().getX() < min_x_value)
      min_x_value = tile->getPosition().getX();
  }

  return min_x_value;
}

//------------------------------------------------------------------------------
int GameLib::Game::getMaxYValue() const
{
  int max_y_value;

  if(tiles_.empty())
    throw NoTilesLeftException("there are no tiles");

  max_y_value = tiles_.at(0)->getPosition().getY();

  for(unsigned int tiles_index = 1; tiles_index < tiles_.size(); tiles_index++)
  {
    TilePtr tile = tiles_.at(tiles_index);

    if(tile->getPosition().getY() > max_y_value)
      max_y_value = tile->getPosition().getY();
  }

  return max_y_value;
}

//------------------------------------------------------------------------------
int GameLib::Game::getMinYValue() const
{
  int min_y_value;

  if(tiles_.empty())
    throw NoTilesLeftException("there are no tiles");

  min_y_value = tiles_.at(0)->getPosition().getY();

  for(unsigned int tiles_index = 1; tiles_index < tiles_.size(); tiles_index++)
  {
    TilePtr tile = tiles_.at(tiles_index);

    if(tile->getPosition().getY() < min_y_value)
      min_y_value = tile->getPosition().getY();
  }

  return min_y_value;
}

//------------------------------------------------------------------------------
unsigned int GameLib::Game::getTileCount() const
{
  return tiles_.size();
}

//------------------------------------------------------------------------------
unsigned int GameLib::Game::getMaxOfTiles()
{
  return MAX_OF_TILES;
}

//------------------------------------------------------------------------------
void GameLib::Game::tooglePlayer()
{
  active_player_ = getPausedPlayer();
}

//------------------------------------------------------------------------------
TileTypeLib::Edge GameLib::Game::getTouchingEdge(Position first, Position second)
const
{
  int offset_x = first.getX() - second.getX();
  int offset_y = first.getY() - second.getY();

  if(abs(offset_x) > 0 && offset_x > 0)
    return TileTypeLib::Edge::LEFT;
  if(abs(offset_x) > 0 && offset_x < 0)
    return TileTypeLib::Edge::RIGHT;
  if(abs(offset_y) > 0 && offset_y > 0)
    return TileTypeLib::Edge::BOTTOM;

  return TileTypeLib::Edge::TOP;
}
