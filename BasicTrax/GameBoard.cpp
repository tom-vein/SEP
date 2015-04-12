#include "GameBoard.h"

GameBoard::GameBoard(const GameLib::Game& game, const std::string& file_name) :
  game_(game)
{
  if(!file_name.empty())
  {
    file_manager_.setFileName(file_name);
    should_write_to_file_ = true;
  }
}

void GameBoard::startGame()
{

}

bool GameBoard::canTileBePlaced(const Tile& tile_to_add) const
{

  return false;
}

void GameBoard::doTurn(const Tile& tile) throw(InvalidPositionException)
{
  if(!canTileBePlaced(tile))
    throw InvalidPositionException("TODO cant be placed", tile.getPosition());

  addTile(tile);
  doForcedPlay(tile);
}
void GameBoard::addTile(const Tile& tile_to_add)
{

}
void GameBoard::doForcedPlay(const Tile& last_placed)
{

}
