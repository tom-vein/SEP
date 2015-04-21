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
  static TileTypeLib::TileType parseTileType(const std::string& input,
                                              const GameLib::Game& game);
  static std::string lowerChars(const std::string& data);

public:
  //Here all checks are done and for the further steps it will be determined
  //that the command is and its parameters are valid and do not needed to be
  //checked again
  static std::shared_ptr<CommandLib::Command> parseCommand(
      const std::string& command_string, const GameLib::Game& game);
  static std::string parseArguments(int argc, char* argv[]);

};

#endif // PARSER_H
