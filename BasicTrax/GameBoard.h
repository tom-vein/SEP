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

  void doForcedPlay();
  bool checkWin();
  bool canTileBePlaced() const; //are colors of edges correct
public:
  GameBoard(const GameLib::Game& game, const std::string& file_name);
  void startGame();
  void doTurn();
};

#endif // GAMEBOARD_H
