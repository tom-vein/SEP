#ifndef GAMEBOARD_H
#define GAMEBOARD_H

class Game;

class GameBoard
{
private:
  Game game_;
public:
  GameBoard(Game game);
  void run();
};

#endif // GAMEBOARD_H
