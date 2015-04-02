#include "DoTurnCommand.h"

#include "GameBoard.h"

virtual CommandLib::Code DoTurnCommand::execute(GameBoard& game_board)
{
  game_board.doTurn();
}
