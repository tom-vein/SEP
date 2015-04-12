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
}

CommandLib::StartGameCommand::~StartGameCommand()
{

}

const std::string& CommandLib::StartGameCommand::getFileName() const
{
  return file_name_;
}

CommandLib::DoTurnCommand::DoTurnCommand(std::shared_ptr<Tile> tile) : tile_(tile)
{

}

CommandLib::Code CommandLib::DoTurnCommand::execute(GameBoard& game_board) const
{
  game_board.doTurn(tile_);
}

CommandLib::DoTurnCommand::~DoTurnCommand()
{
}

CommandLib::Code CommandLib::QuitCommand::execute(GameBoard& game_board) const
{
  //Maybe some quit actions in game_board!!!!!!
  return Code::QUIT;
}

CommandLib::QuitCommand::~QuitCommand()
{
}
