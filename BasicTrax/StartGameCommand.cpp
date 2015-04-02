#include "StartGameCommand.h"
#include "GameBoard.h"

virtual CommandLib::Code StartGameCommand::execute(GameBoard& game_board)
{
  game_board.startGame();
}
