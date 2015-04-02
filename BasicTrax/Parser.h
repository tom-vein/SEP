#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <memory>
#include "Command.h"

class Parser
{
public:
  //Here all checks are done and for the further steps it will be determined
  //that the command is and its parameters are valid and do not needed to be
  //checked again
  static std::unique_ptr<CommandLib::Command> parseCommand(
      const std::string& command_string);
  static std::string parseArguments(int argc, char* argv[]);
};

#endif // PARSER_H
