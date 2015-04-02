#ifndef ADDTILECOMMAND_H
#define ADDTILECOMMAND_H

#include "Command.h"

class GameBoard;

class DoTurnCommand : public Command
{
public:
  DoTurnCommand();
  virtual CommandLib::Code execute(GameBoard& game_board) const override;
  virtual ~DoTurnCommand() override;
};

#endif // ADDTILECOMMAND_H
