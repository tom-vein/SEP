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

void GameBoard::doTurn(std::shared_ptr<Tile> tile_to_add) throw(std::exception*)
{
  if(!canTileBePlaced(tile_to_add))
    throw new std::exception("TODO cant be placed");
  addTile(tile_to_add);
  doForcedPlay(tile_to_add);
}

bool GameBoard::canTileBePlaced(std::shared_ptr<Tile> tile_to_add)
{

}
