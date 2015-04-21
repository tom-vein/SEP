#include "Parser.h"
#include "Position.h"

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
    throw std::exception();
  }

  istr >> x;
  istr >> none;

  if(none != ',')
  {
    x = 0;
    y = 0;
    throw std::exception();
  }

  istr >> y;
  istr >> none;

  if(none != ')')
  {
    x = 0;
    y = 0;
    throw std::exception();
  }

  istr >> none;

  if(!istr.eof())
  {
    x = 0;
    y = 0;
    throw std::exception();
  }

  return Position(x, y);
}


std::string Parser::lowerChars(const std::string& data)
{
  std::string str = data;
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}


TileTypeLib::TileType Parser::parseTileType(const std::string& input,
                                            const GameLib::Game& game)
{

  if(input == "x")
    return TileTypeLib::TileType::getTileType(
          TileTypeLib::Shape::CROSS, game.getActivePlayer().getColor());

  if(input == "/")
    return TileTypeLib::TileType::getTileType(
          TileTypeLib::Shape::CURVE_TOP_LEFT_CORNER,
          game.getActivePlayer().getColor());

  if(input == "\\")
    return TileTypeLib::TileType::getTileType(
          TileTypeLib::Shape::CURVE_TOP_RIGHT_CORNER,
          game.getActivePlayer().getColor());

  throw std::exception(); //if not "+, /, \"

}

std::shared_ptr<CommandLib::Command> Parser::parseCommand(
    const std::string& command_string, const GameLib::Game& game)
{

  std::string command;
  std::string param;
  std::string filename_or_tiletype;
  std::string rest;
  std::istringstream full_command(Parser::lowerChars(command_string));
  full_command >> command >> param >> filename_or_tiletype >> rest;

  if(command == "./basic")
  {
    if(param == "-g")
    {
      if(!filename_or_tiletype.empty() && rest.empty())
      {
        return std::shared_ptr<CommandLib::Command>
            (new CommandLib::StartGameCommand(filename_or_tiletype));
      }
      throw std::exception(); //when no filename or unused param at the end
    }
    if(param.empty())
    {
      return std::shared_ptr<CommandLib::Command>
          (new CommandLib::StartGameCommand(""));
    }
    throw std::exception(); //wrong param not "-g"
  }

  if(command == "quit")
  {
    if(param.empty())
    {
      return std::shared_ptr<CommandLib::Command>
          (new CommandLib::QuitCommand());
    }
    throw std::exception(); //too much param after quit command
  }

  if(command == "addtile")
  {
    if(!param.empty() && !filename_or_tiletype.empty() && (rest.empty()))
    {
      Position needed_Position = Parser::parsePosition(param);
      TileTypeLib::TileType needed_Tile_Type =
          Parser::parseTileType(filename_or_tiletype, game);
      std::shared_ptr<Tile> newTile
          (new Tile(needed_Tile_Type, needed_Position));
      return std::shared_ptr<CommandLib::Command>
          (new CommandLib::DoTurnCommand(newTile));
    }
    throw std::exception(); //when param empty filename empty or too much param rest
  }


  if(command == "write")
  {
    if(!param.empty() && filename_or_tiletype.empty())
    {
      return std::shared_ptr<CommandLib::WriteCommand>
          (new CommandLib::WriteCommand(param));
    }
  }
  throw std::exception(); //filename missing or too much params rest
}

std::string Parser::parseArguments(int argc, char* argv[])
{
  if(argc == 1)
    return std::string(argv[0]);

  if(argc == 3)
  {
    std::stringstream ss;
    ss << argv[0] << ' ' << argv[1] << ' ' << argv[2];
    return ss.str();
  }

  throw std::exception(); //wrong number of arguments
}
