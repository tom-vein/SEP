//------------------------------------------------------------------------------
// Parser.h
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>
#include "Command.h"

//------------------------------------------------------------------------------
// Parser Class
//
//
class Parser
{
private:

  //--------------------------------------------------------------------------
  // Private Methods that are used while parsing Commands
  //
  static Position parsePosition(const std::string& input);
  static TileTypeLib::Shape parseTileTypeShape(const std::string& input);
  static std::string lowerChars(const std::string& data);

public:

  //--------------------------------------------------------------------------
  // Public Method responsible to parse all kind of Commands
  //
  static std::shared_ptr<CommandLib::Command> parseCommand(
      const std::string& command_string);

  //--------------------------------------------------------------------------
  // Public Method responsible to parse number of Arguments and Correctness
  //
  static std::shared_ptr<CommandLib::Command> parseArguments(
      int argc, char* argv[]);
};

#endif // PARSER_H
