#ifndef STARTGAMECOMMAND_H
#define STARTGAMECOMMAND_H

#include "Command.h"

class GameBoard;

class StartGameCommand : public Command
{
public:
  StartGameCommand();
  virtual CommandLib::Code execute(GameBoard& game_board) const override;
  virtual ~StartGameCommand() override;
};

#endif // STARTGAMECOMMAND_H
