#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>
#include "Command.h"

class Parser
{
public:
  //Here all checks are done and for the further steps it will be determined
  //that the command is and its parameters are valid and do not needed to be
  //checked again
  static std::shared_ptr<CommandLib::Command> parseCommand(
      const std::string& command_string);
  static std::string parseArguments(int argc, char* argv[]);
  static void parsePosition(const std::string& input);
  static void parseTileType(const std::string& input);
};

#endif // PARSER_H
