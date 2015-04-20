#include "Parser.h"
#include <string>
#include <sstream>

std::shared_ptr<CommandLib::Command> Parser::parseCommand(
    const std::string& command_string)
{
  int commandsize = command_string.size();

  if(command_string.at(5) == '-' && command_string.at(6) == 'g') //parse "-g"
  {
    for(unsigned int i = 9; i <= commandsize; i++)
    {
      std::string filename;
      filename.push_back(command_string.at(i));
    }
    CommandLib::StartGameCommand(filename); //create StartGameCommand w. filename
    return command_string; //return korrekt?
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
