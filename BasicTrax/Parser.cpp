#include "Parser.h"
#include <string>

std::shared_ptr<CommandLib::Command> Parser::parseCommand(
    const std::string& command_string)
{

}

std::string Parser::parseArguments(int argc, char* argv[])
{
  if(argc == 1 || argc == 3)
  {
    std::vector<std::string> all_args(argv, argv + argc);
    return all_args;
  }
  else
  {
    std::string errorstring("Wrong Number of Arguments");
    CommandLib::ErrorCommand(errorstring);
    //return?
  }
}
