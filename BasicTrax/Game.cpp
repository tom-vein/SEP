#include "Game.h"
#include <utility>

GameLib::Game::Game(const std::array<Player, 2>& players) :
  players_(players), active_player_(players_.at(0))
{

}

TilePtr GameLib::Game::getTileByPosition(const Position& position,
                                         int offset_x, int offset_y) const
throw(InvalidPositionException)
{
  Position position_to_return(position.getX() + offset_x,
                              position.getY() + offset_y);
  for(TilePtr tile : tiles_)
  {
    if(tile->getPosition() == position_to_return)
      return tile;
  }

  return nullptr;
}

void GameLib::Game::addTile(TilePtr to_add)
throw(NoTilesLeftException)
{
  if(tiles_.size() >= MAX_OF_TILES)
    throw NoTilesLeftException("Invalid move - not enough tiles left");

  tiles_.push_back(to_add);
  ++num_of_placed_tiles_in_current_turn_;
}

void GameLib::Game::removeTileAtPosition(const Position& position)
throw(InvalidPositionException)
{
  for(std::vector<TilePtr>::iterator it = tiles_.begin();
      it != tiles_.end(); it++)
  {
    if( (*it)->getPosition() == position)
    {
      tiles_.erase(it);
      --num_of_placed_tiles_in_current_turn_;
      return;
    }
  }
  throw(InvalidPositionException("No Tile with this position.", position));
}

void GameLib::Game::removeTile(TilePtr tile_to_remove)
{
  for(std::vector<TilePtr>::iterator it = tiles_.begin();
      it != tiles_.end(); it++)
  {
    if( (*it) == tile_to_remove)
    {
      tiles_.erase(it);
      --num_of_placed_tiles_in_current_turn_;
      return;
    }
  }
  throw(InvalidPositionException("No Tile with this position.",
                                 tile_to_remove->getPosition()));
}

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

std::map<TileTypeLib::Edge, Color> GameLib::Game::getTouchingColors(
    const Position &position, int offset_x, int offset_y) const
{
  std::map<TileTypeLib::Edge, Color> touching_colors;
  TilePtr tile;
  //Left
  if(tile = getTileByPosition(position, offset_x - 1, offset_y))
    touching_colors[TileTypeLib::Edge::LEFT] =
        tile->getColorAtEdge(TileTypeLib::Edge::RIGHT);
  else
    touching_colors[TileTypeLib::Edge::LEFT] = Color::NONE;

  //Top
  if(tile = getTileByPosition(position, offset_x, offset_y - 1))
    touching_colors[TileTypeLib::Edge::TOP] =
        tile->getColorAtEdge(TileTypeLib::Edge::BOTTOM);
  else
    touching_colors[TileTypeLib::Edge::TOP] = Color::NONE;

  //Right
  if(tile = getTileByPosition(position, offset_x + 1, offset_y))
    touching_colors[TileTypeLib::Edge::RIGHT] =
        tile->getColorAtEdge(TileTypeLib::Edge::LEFT);
  else
    touching_colors[TileTypeLib::Edge::RIGHT] = Color::NONE;

  //Bottom
  if(tile = getTileByPosition(position, offset_x, offset_y + 1))
    touching_colors[TileTypeLib::Edge::BOTTOM] =
        tile->getColorAtEdge(TileTypeLib::Edge::TOP);
  else
    touching_colors[TileTypeLib::Edge::BOTTOM] = Color::NONE;

  return touching_colors;
}

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
                                       osition.getY() + offset_y + 1));

  return empty_positions;
}

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

const Player& GameLib::Game::getActivePlayer() const
{
  return active_player_;
}

const Player& GameLib::Game::getPausedPlayer() const
{
  if(active_player_ == players_.at(0))
    return players_.at(1);

  if(active_player_ == players_.at(1))
    return players_.at(0);

  throw MessageException("No suitable paused player found!!!");
}

int GameLib::Game::getMaxXValue() const
{
  int max_x_value;

  if(tiles_.empty())
    throw NoTilesLeftException("there are no tiles");

  max_x_value = tiles_.at(0)->getPosition().getX();

  for(unsigned int i = 1; i < tiles_.size(); i++)
  {
    TilePtr tile = tiles_.at(i);

    if(tile->getPosition().getX() > max_x_value)
      max_x_value = tile->getPosition().getX();
  }

  return max_x_value;
}

int GameLib::Game::getMinXValue() const
{
  int min_x_value;

  if(tiles_.empty())
    throw NoTilesLeftException("there are no tiles");

  min_x_value = tiles_.at(0)->getPosition().getX();

  for(unsigned int i = 1; i < tiles_.size(); i++)
  {
    TilePtr tile = tiles_.at(i);

    if(tile->getPosition().getX() < min_x_value)
      min_x_value = tile->getPosition().getX();
  }

  return min_x_value;
}

int GameLib::Game::getMaxYValue() const
{
  int max_y_value;

  if(tiles_.empty())
    throw NoTilesLeftException("there are no tiles");

  max_y_value = tiles_.at(0)->getPosition().getY();

  for(unsigned int i = 1; i < tiles_.size(); i++)
  {
    TilePtr tile = tiles_.at(i);

    if(tile->getPosition().getY() > max_y_value)
      max_y_value = tile->getPosition().getX();
  }

  return max_y_value;
}

int GameLib::Game::getMinYValue() const
{
  int min_y_value;

  if(tiles_.empty())
    throw NoTilesLeftException("there are no tiles");

  min_y_value = tiles_.at(0)->getPosition().getY();

  for(unsigned int i = 1; i < tiles_.size(); i++)
  {
    TilePtr tile = tiles_.at(i);

    if(tile->getPosition().getY() < min_y_value)
      min_y_value = tile->getPosition().getX();
  }

  return min_y_value;
}

unsigned int GameLib::Game::getTileCount() const
{
  return tiles_.size();
}

unsigned int GameLib::Game::getMaxOfTiles()
{
  return MAX_OF_TILES;
}

void GameLib::Game::tooglePlayer()
{
  active_player_ = getPausedPlayer();
}
