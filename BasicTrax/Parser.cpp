#include "Parser.h"
#include <string>
#include <sstream>

std::shared_ptr<CommandLib::Command> Parser::parseCommand(
    const std::string& command_string)
{
  if(command_string.at(5) == '-' && command_string.at(6) == 'g')
  {
    for(int i=9; i <= command_string.size(); i++) //range based schl?
    {
      std::string filename;
      filename.push_back(command_string.at(i));
    }
   // CommandLib::StartGameCommand(filename);
    //return command_string;
  }
  //if(command_string == CommandLib::Code::QUIT)
  {
   // CommandLib::QuitCommand::Command(CommandLib::Code::QUIT); // ????
   // return command_string;
  }
  //throw exception;
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
