#include "Parser.h"
#include <string>

std::shared_ptr<CommandLib::Command> Parser::parseCommand(
    const std::string& command_string)
{

}

std::string Parser::parseArguments(int argc, char* argv[])
{

  if(argc == 1)
    return std::string(argv[0]);

  if(argc == 3)
    return std::string(argv[0], argv[1], argv[2]);

  throw exception();

}
