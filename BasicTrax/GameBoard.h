#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "FileManager.h"
#include "Game.h"

class GameBoard
{
private:
  GameLib::Game game_;
  FileManager file_manager_; //Before writing look if should_write_to_file_ is
                             //set to true
  bool should_write_to_file_;

  void doForcedPlay(std::shared_ptr<Tile> last_placed);
  bool checkWin();
  bool canTileBePlaced(std::shared_ptr<Tile> tile_to_check) const; //are colors of edges correct
  void addTile(std::shared_ptr<Tile> tile_to_add);
  std::shared_ptr<Tile> getTileByPosition(Position position);
public:
  GameBoard(const GameLib::Game& game, const std::string& file_name);
  void startGame();
  void doTurn(const Tile& tile) throw(std::exception*);
};

#endif // GAMEBOARD_H
