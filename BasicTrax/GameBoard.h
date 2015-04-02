#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "FileManager.h"
#include "Game.h"

class GameBoard
{
private:
  GameLib::Game game_;
  FileManager file_manager_;

  void doForcedPlay();
  bool checkWin();
  bool canTileBePlaced(); //are colors of edges correct

public:
  GameBoard(const GameLib::Game& game);
  void startGame();
  void doTurn();
};

#endif // GAMEBOARD_H
