#include "Parser.h"
#include "Position.h"

Position Parser::parsePosition(const std::string& input) //parse '(' usw. for addtile
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

//TileTypeLib::TileType Parser::parseTileType(const std::string& input,
//                                            const GameLib::Game& game)
//{

//  if(input == "x")
//    return TileTypeLib::TileType::getTileType(TileTypeLib::Shape::CROSS, GameLib::Game::); ///????

//  if(input == "/")
//    return 0;

//  if(input == "\"")

//  throw std::exception();

//}


std::shared_ptr<CommandLib::Command> Parser::parseCommand(
    const std::string& command_string, const GameLib::Game& game)
{
  int commandsize = command_string.size();

  if(command_string.at(5) == '-' && command_string.at(6) == 'g') //parse "-g"
  {
    std::string filename;
    for(int i = 9; i <= commandsize; i++)
      filename.push_back(command_string.at(i));

    return std::shared_ptr<CommandLib::Command>
        (new CommandLib::StartGameCommand(filename));
  }

  if(commandsize == 3) //parse "quit"
  {
    std::string quit = "quit";
    for (int i = 0; i <= commandsize; i++)
        if (tolower(command_string.at(i)) != quit.at(i))
          throw std::exception();

    return std::shared_ptr<CommandLib::Command>(new CommandLib::QuitCommand());

  }

  if(commandsize == 6) //parse "addtile"
  {
    std::string addtile = "addtile";
    for (int i = 0; i <= commandsize; i++)
        if (tolower(command_string.at(i)) != addtile.at(i))
          throw std::exception();

    std::istringstream iss(command_string);
    std::vector<std::string> tokens;
    copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         back_inserter(tokens)); //saves param to own vector

    Position needed_Position = Parser::parsePosition(tokens.at(1)); //to check (x,y) ret. position
//    TileTypeLib::TileType needed_Tile_Type =
//        Parser::parseTileType(tokens.at(2), game);

  }
  throw std::exception();
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

  throw std::exception();
}
