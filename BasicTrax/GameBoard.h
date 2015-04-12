#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "FileManager.h"
#include "Game.h"
#include "Exceptions.h"

class GameBoard
{
private:
  GameLib::Game game_;
  FileManager file_manager_; //Before writing look if should_write_to_file_ is
                             //set to true

  std::vector<Position> tired_insertions_; // used for rollback when invalid move would be made
  bool should_write_to_file_;

  void doForcedPlay(const Tile& last_placed);
  bool checkWin();
  bool canTileBePlaced(const Tile& tile_to_check) const; //are colors of edges correct
  void addTile(const Tile& tile_to_add);


public:
  GameBoard(const GameLib::Game& game, const std::string& file_name);
  void startGame();
  void doTurn(const Tile& tile)
    throw(InvalidPositionException);
};

#endif // GAMEBOARD_H
