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

bool GameBoard::canTileBePlaced(std::shared_ptr<Tile> tile_to_add)
{
  return false;
}

void GameBoard::doTurn(const Tile& tile) throw(std::exception*)
{
  if(!canTileBePlaced(tile))
    throw new std::exception("TODO cant be placed");
  addTile(tile);
  doForcedPlay(tile);
}
