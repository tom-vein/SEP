#include "Parser.h"
#include "Position.h"
#include "Exceptions.h"

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
     throw WrongParameterException("Invalid parameters\n");
  }

  istr >> x;
  istr >> none;

  if(none != ',')
  {
    x = 0;
    y = 0;
     throw WrongParameterException("Invalid parameters\n");
  }

  istr >> y;
  istr >> none;

  if(none != ')')
  {
    x = 0;
    y = 0;
     throw WrongParameterException("Invalid parameters\n");
  }

  istr >> none;

  if(!istr.eof())
  {
    x = 0;
    y = 0;
     throw WrongParameterException("Invalid parameters\n");
  }

  return Position(x, y);
}


std::string Parser::lowerChars(const std::string& data)
{
  std::string str = data;
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}


TileTypeLib::Shape Parser::parseTileTypeShape(const std::string& input)
{

  if(input == "+")
    return TileTypeLib::Shape::CROSS;

  if(input == "/")
    return TileTypeLib::Shape::CURVE_TOP_LEFT_CORNER;

  if(input == "\\")
    return TileTypeLib::Shape::CURVE_TOP_RIGHT_CORNER;

  throw WrongParameterException("Invalid parameters"); //if not "+, /, \"

}

std::shared_ptr<CommandLib::Command> Parser::parseCommand(
    const std::string& command_string)
{
  if(command_string.empty())
    return nullptr;

  std::string command;
  std::string param;
  std::string filename_or_tiletype;
  std::string rest;
  std::istringstream full_command(Parser::lowerChars(command_string));
  full_command >> command >> param >> filename_or_tiletype >> rest;

  if(command == "quit")
  {
    if(param.empty())
    {
      return std::shared_ptr<CommandLib::Command>
          (new CommandLib::QuitCommand());
    }
    throw(WrongParameterException("Error: Wrong parameter count!")); //too much param after quit command
  }

  if(command == "addtile")
  {
    if(!param.empty() && !filename_or_tiletype.empty() && (rest.empty()))
    {
      Position needed_Position = Parser::parsePosition(param);
      TileTypeLib::Shape needed_Shape =
          Parser::parseTileTypeShape(filename_or_tiletype);

//      std::shared_ptr<Tile> newTile
//          (new Tile(needed_Shape, needed_Position));
// ///////////// Vali Problem Ausbesserung
//      return std::shared_ptr<CommandLib::Command>
//          (new CommandLib::DoTurnCommand(newTile));

      return std::shared_ptr<CommandLib::Command>
          (new CommandLib::DoTurnCommand(needed_Position, needed_Shape));
    }
    throw(WrongParameterException("Error: Wrong parameter count!"));
  }


  if(command == "write")
  {
    if(!param.empty() && filename_or_tiletype.empty())
    {
      return std::shared_ptr<CommandLib::WriteCommand>
          (new CommandLib::WriteCommand(param));
    }
  }


  throw(WrongParameterException("Error: Unknown command!"));
}

std::shared_ptr<CommandLib::Command> Parser::parseArguments(
    int argc, char* argv[])
{
  if(argc == 1)
  {
    return std::shared_ptr<CommandLib::Command>(new CommandLib::StartGameCommand(""));
  }

  if(argc == 3 && std::string(argv[1]) == "-g" &&
     !(std::string(argv[2])).empty())
  {
    return std::shared_ptr<CommandLib::Command>(new CommandLib::StartGameCommand(argv[2]));
  }

  std::string error_message = "Usage: " + std::string(argv[0]);
  throw WrongUsageProgramException(error_message);
}
