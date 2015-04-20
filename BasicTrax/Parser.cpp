#include "Parser.h"
#include "Position.h"

static Position Parser::parsePosition(const std::string& input) //parse '(' usw. for addtile
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
    throw exception;
  }

  istr >> x;
  istr >> none;

  if(none != ',')
  {
    x = 0;
    y = 0;
    throw exception;
  }

  istr >> y;
  istr >> none;

  if(none != ')')
  {
    x = 0;
    y = 0;
    throw exception;
  }

  istr >> none;

  if(!istr.eof())
  {
    x = 0;
    y = 0;
    throw exception;
  }

  return Position::Position(x, y);
}

static TileTypeLib::TileType Parser::parseTileType(const std::string& input)
{

}


std::shared_ptr<CommandLib::Command> Parser::parseCommand(
    const std::string& command_string)
{
  int commandsize = command_string.size();

  if(command_string.at(5) == '-' && command_string.at(6) == 'g') //parse "-g"
  {
    std::string filename;
    for(unsigned int i = 9; i <= commandsize; i++)
    {
      filename.push_back(command_string.at(i));
    }
    CommandLib::StartGameCommand(filename); //create StartGameCommand w. filename
    return filename; //return korrekt?
  }

  if(commandsize == 3) //parse "quit"
  {
    std::string quit = 'quit';
    for (unsigned int i = 0; i <= commandsize; i++)
        if (tolower(command_string.at(i)) != quit.at(i))
          throw exception;
    CommandLib::QuitCommand(command_string); //create QuitCommand
    return command_string;
  }

  if(commandsize == 6) //parse "addtile"
  {
    std::string addtile = 'addtile';
    for (unsigned int i = 0; i <= commandsize; i++)
        if (tolower(command_string.at(i)) != addtile.at(i))
          throw exception;
    std::istringstream iss(command_string);
    std::vector<string> tokens;
    copy(istream_iterator<string>(iss), istream_iterator<string>(),
         back_inserter(tokens)); //saves param to own vector
    Position = Parser::parsePosition(tokens.at(1)); //to check (x,y) ret. position
    TileTypeLib::TileType = Parser::parseTileType(tokens.at(2));

  }


  throw exception;
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

//  throw exception();
}
