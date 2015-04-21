//------------------------------------------------------------------------------
// Filename: Command.cpp
// Description: Class representing a general command
// Authors: Tutors
// Tutor: Tutors
// Group: 42
// Created: 02.09.2011
// Last change: 02.09.2011
//------------------------------------------------------------------------------

#include "Command.h"

std::shared_ptr<CommandLib::Command> CommandLib::readCommand(
    const GameLib::Game& game)
{

}

//------------------------------------------------------------------------------
CommandLib::Command::~Command()
{
}

CommandLib::StartGameCommand::StartGameCommand(const std::string& file_name) :
  file_name_(file_name)
{

}

CommandLib::Code CommandLib::StartGameCommand::execute(GameBoard& game_board)
const
{
  game_board.startGame();

  return Code::START;
}

CommandLib::StartGameCommand::~StartGameCommand()
{

}

const std::string& CommandLib::StartGameCommand::getFileName() const
{
  return file_name_;
}

CommandLib::DoTurnCommand::DoTurnCommand(TilePtr tile) : tile_(tile)
{

}

CommandLib::Code CommandLib::DoTurnCommand::execute(GameBoard& game_board) const
{
  game_board.doTurn(tile_);

  if(game_board.hasWinner())
    return Code::WIN;

  if(game_board.isDraw())
    return Code::DRAW;

  return Code::CONTINUE;
}

CommandLib::DoTurnCommand::~DoTurnCommand()
{
}

CommandLib::Code CommandLib::QuitCommand::execute(GameBoard&) const
{
  return Code::QUIT;
}

CommandLib::QuitCommand::~QuitCommand()
{
}

CommandLib::ErrorCommand::ErrorCommand(std::string message) : message_(message)
{
}

CommandLib::Code CommandLib::ErrorCommand::execute(GameBoard&) const
{
  std::cout << message_ << std::endl;
  return Code::CONTINUE;
}

CommandLib::ErrorCommand::~ErrorCommand()
{
}


CommandLib::WriteCommand::WriteCommand(std::string file_name)
  : file_name_(file_name)
{
}

CommandLib::Code CommandLib::WriteCommand::execute(GameBoard& game_board) const
{
  game_board.write(file_name_);

  return Code::CONTINUE;
}

CommandLib::WriteCommand::~WriteCommand()
{
}
