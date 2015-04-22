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
private:
  static Position parsePosition(const std::string& input);
  static TileTypeLib::Shape parseTileTypeShape(const std::string& input);
  static std::string lowerChars(const std::string& data);

public:
  static std::shared_ptr<CommandLib::Command> parseCommand(
      const std::string& command_string);
  static std::shared_ptr<CommandLib::Command> parseArguments(
      int argc, char* argv[]);

};

#endif // PARSER_H
