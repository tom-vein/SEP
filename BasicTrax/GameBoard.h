#ifndef GAMEBOARD_H
#define GAMEBOARD_H

class Game;
class Command;

class GameBoard
{
private:
  Game game_;
public:
  GameBoard(Game& game);
  void executeCommand(const Command& command);
};

#endif // GAMEBOARD_H
