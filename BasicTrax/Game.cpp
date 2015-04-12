#include "Game.h"

GameLib::Game::Game(const std::array<PlayerLib::Player, 2>& players) :
  players_(players), active_player_(players_.at(0))
{

}

std::shared_ptr<Tile> GameLib::Game::getTileByPosition(const Position& position, int offset_x, int offset_y)
  throw(InvalidPositionException)
{
  Position position_to_return(position.getX() + offset_x, position.getY() + offset_y);
  for(std::vector<std::shared_ptr<Tile>>::iterator it = tiles_.begin(); it != tiles_.end(); it++)
  {
   if( (*it)->getPosition() == position_to_return)
     return *it;
  }
  throw InvalidPositionException("No Tile at this Position.", position);
}
