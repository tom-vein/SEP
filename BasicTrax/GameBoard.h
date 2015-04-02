#ifndef GAMEBOARD_H
#define GAMEBOARD_H

class Game;
class Command;
class FileManager;

class GameBoard
{
private:
  Game game_;
  FileManager file_manager_;
  void doForcedPlay();
  bool checkWin();
  bool canTileBePlaced(); //are colors of edges correct

public:
  GameBoard(Game& game);
  void startGame();
  void doTurn();
};

#endif // GAMEBOARD_H
