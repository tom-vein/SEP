//------------------------------------------------------------------------------
// Parser.cpp
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#include "Parser.h"
#include "Position.h"
#include "Exceptions.h"

//------------------------------------------------------------------------------
Position Parser::parsePosition(const std::string& input)
{
  char none;
  std::istringstream istr;
  istr.str(input);
  int x;
  int y;

  istr >> none;

  if(none != '(')
  {
    x = 0;
    y = 0;
     throw WrongParameterException("Invalid parameters");
  }

  istr >> x;
  istr >> none;

  if(none != ',')
  {
    x = 0;
    y = 0;
     throw WrongParameterException("Invalid parameters");
  }

  istr >> y;
  istr >> none;

  if(none != ')')
  {
    x = 0;
    y = 0;
     throw WrongParameterException("Invalid parameters");
  }

  istr >> none;

  if(!istr.eof())
  {
    x = 0;
    y = 0;
     throw WrongParameterException("Invalid parameters");
  }
  return Position(x, y);
}

//------------------------------------------------------------------------------
std::string Parser::lowerChars(const std::string& input)
{
  std::string str = input;
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

//------------------------------------------------------------------------------
TileTypeLib::Shape Parser::parseTileTypeShape(const std::string& input)
{
  if(input == "+")
    return TileTypeLib::Shape::CROSS;

  if(input == "/")
    return TileTypeLib::Shape::CURVE_TOP_LEFT_CORNER;

  if(input == "\\")
    return TileTypeLib::Shape::CURVE_TOP_RIGHT_CORNER;

  throw WrongParameterException("Invalid parameters");
}

//------------------------------------------------------------------------------
std::shared_ptr<CommandLib::Command> Parser::parseCommand(
    const std::string& command_string)
{
  if(command_string.empty())
    return nullptr;

  std::string command;
  std::string part_2;
  std::string part_3;
  std::string rest;
  std::istringstream full_command(Parser::lowerChars(command_string));
  full_command >> command >> part_2 >> part_3 >> rest;

  if(command == "quit")
  {
    if(part_2.empty())
    {
      return std::shared_ptr<CommandLib::Command>
          (new CommandLib::QuitCommand());
    }
    throw(WrongParameterException("Error: Wrong parameter count!"));
  }

  if(command == "addtile")
  {
    if(!part_2.empty() && !part_3.empty() && (rest.empty()))
    {
      Position needed_Position = Parser::parsePosition(part_2);
      TileTypeLib::Shape needed_Shape =
          Parser::parseTileTypeShape(part_3);
      return std::shared_ptr<CommandLib::Command>
          (new CommandLib::DoTurnCommand(needed_Position, needed_Shape));
    }
    throw(WrongParameterException("Error: Wrong parameter count!"));
  }

  if(command == "write")
  {
    if(!part_2.empty() && part_3.empty())
    {
      return std::shared_ptr<CommandLib::WriteCommand>
          (new CommandLib::WriteCommand(part_2));
    }
    throw(WrongParameterException("Error: Wrong parameter count!"));
  }

  if(command == "whoami")
  {
    if(part_2.empty())
    {
      return std::shared_ptr<CommandLib::Command>
          (new CommandLib::WhoAmICommand());
    }
    throw(WrongParameterException("Error: Wrong parameter count!"));
  }

  if(command == "play")
  {
    if(part_2.empty())
    {
      return std::shared_ptr<CommandLib::Command>
          (new CommandLib::PlayCommand());
    }
    throw(WrongParameterException("Error: Wrong parameter count!"));
  }

  throw(WrongParameterException("Error: Unknown command!"));
}

//------------------------------------------------------------------------------
std::shared_ptr<CommandLib::Command> Parser::parseArguments(
    int argc, char* argv[])
{
  if(argc == 1)
  {
    return std::shared_ptr<CommandLib::Command>
        (new CommandLib::StartGameCommand(""));
  }

  if(argc == 3 && std::string(argv[1]) == "-g" &&
     !(std::string(argv[2])).empty())
  {
    return std::shared_ptr<CommandLib::Command>
        (new CommandLib::StartGameCommand(argv[2]));
  }
  std::string error_message = "Usage: " + std::string(argv[0]);
  throw WrongUsageProgramException(error_message.c_str());
}
