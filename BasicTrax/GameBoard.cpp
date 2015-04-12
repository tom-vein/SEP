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

bool GameBoard::canTileBePlaced(std::shared_ptr<Tile> tile_to_add) const
{

  return false;
}

void GameBoard::doTurn(std::shared_ptr<Tile> tile)
  throw(InvalidPositionException)
{
  if(!canTileBePlaced(tile))
    throw InvalidPositionException("TODO cant be placed", tile->getPosition());

  game_.addTile(tile);
  doForcedPlay(tile);
}
void GameBoard::addTile(std::shared_ptr<Tile> tile_to_add)
{

}
void GameBoard::doForcedPlay(std::shared_ptr<Tile> last_placed)
{

}
