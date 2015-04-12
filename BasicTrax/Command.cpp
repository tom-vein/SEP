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

std::shared_ptr<CommandLib::Command> CommandLib::readCommand()
{

}

//------------------------------------------------------------------------------
CommandLib::Command::Command(const std::string& name) : command_name_(name)
{
}

//------------------------------------------------------------------------------
CommandLib::Command::~Command()
{
}

//------------------------------------------------------------------------------
const std::string& CommandLib::Command::getName() const
{
  return command_name_;
}

CommandLib::Code CommandLib::StartGameCommand::execute(GameBoard& game_board)
const
{
  game_board.startGame();
}

CommandLib::StartGameCommand::~StartGameCommand()
{

}

const std::string& CommandLib::StartGameCommand::getFileName() const
{
  return file_name_;
}

CommandLib::Code CommandLib::DoTurnCommand::execute(GameBoard& game_board) const
{
  game_board.doTurn(tile_);
}

CommandLib::DoTurnCommand::~DoTurnCommand()
{
}
