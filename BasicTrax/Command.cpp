//------------------------------------------------------------------------------
// Command.cpp
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#include "Command.h"
#include "Parser.h"

// Definition of const static variable for the command
const std::string CommandLib::WhoAmICommand::name_ = "todo";

std::shared_ptr<CommandLib::Command> CommandLib::readCommand()
{
  std::string command_str;
  std::cout << "sep> ";
  std::getline (std::cin, command_str);

  std::shared_ptr<Command> command = Parser::parseCommand(command_str);

  return command;
}

//------------------------------------------------------------------------------
CommandLib::Command::~Command()
{
}

//------------------------------------------------------------------------------
CommandLib::StartGameCommand::StartGameCommand(const std::string& file_name) :
  file_name_(file_name)
{

}

//------------------------------------------------------------------------------
CommandLib::Code CommandLib::StartGameCommand::execute(GameBoard&)
const
{
  return Code::START;
}

//------------------------------------------------------------------------------
CommandLib::StartGameCommand::~StartGameCommand()
{

}

//------------------------------------------------------------------------------
const std::string& CommandLib::StartGameCommand::getFileName() const
{
  return file_name_;
}

//------------------------------------------------------------------------------
CommandLib::DoTurnCommand::DoTurnCommand
(const Position& position, TileTypeLib::Shape shape) : position_(position),
  shape_(shape)
{

}

//------------------------------------------------------------------------------
CommandLib::Code CommandLib::DoTurnCommand::execute(GameBoard& game_board) const
{
  game_board.doTurn(position_, shape_);

  if(game_board.hasWinner())
    return Code::WIN;

  if(game_board.isDraw())
    return Code::DRAW;

  return Code::CONTINUE;
}

//------------------------------------------------------------------------------
CommandLib::DoTurnCommand::~DoTurnCommand()
{
}

//------------------------------------------------------------------------------
CommandLib::Code CommandLib::QuitCommand::execute(GameBoard&) const
{
  return Code::QUIT;
}

//------------------------------------------------------------------------------
CommandLib::QuitCommand::~QuitCommand()
{
}

//------------------------------------------------------------------------------
CommandLib::WriteCommand::WriteCommand(std::string file_name)
  : file_name_(file_name)
{
}

//------------------------------------------------------------------------------
CommandLib::Code CommandLib::WriteCommand::execute(GameBoard& game_board) const
{
  try
  {
    game_board.write(file_name_);
  }
  catch(NoTilesLeftException& e)
  {
    std::cout << e.what() << std::endl;
  }

  return Code::CONTINUE;
}

//------------------------------------------------------------------------------
CommandLib::WriteCommand::~WriteCommand()
{
}

//------------------------------------------------------------------------------
CommandLib::WhoAmICommand::WhoAmICommand()
{

}


//------------------------------------------------------------------------------
CommandLib::Code CommandLib::WhoAmICommand::execute(GameBoard &) const
{
  std::cout << CommandLib::WhoAmICommand::name_;
  return Code::CONTINUE;
}

//------------------------------------------------------------------------------
CommandLib::WhoAmICommand::~WhoAmICommand()
{

}


//------------------------------------------------------------------------------
CommandLib::Code CommandLib::PlayCommand::execute(GameBoard& game_board) const
{
  try
  {
    game_board.play();
  }
  catch(MessageException& ex)
  {
    std::cout << ex.what();
  }

  if(game_board.hasWinner())
    return Code::WIN;

  if(game_board.isDraw())
    return Code::DRAW;

  return Code::CONTINUE;
}

//------------------------------------------------------------------------------
CommandLib::PlayCommand::~PlayCommand()
{

}

