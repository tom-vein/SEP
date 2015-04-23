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
// Class to combine all Methods to parse Arguments and Commands
//
class Parser
{
private:

  //--------------------------------------------------------------------------
  // Private Method that is used when parsing addtile Command
  // @param input is second Parameter of a Command which includes Coordinates
  // @return Position Object with Coordinates when Parse is sucessfull
  //
  static Position parsePosition(const std::string& input);

  //--------------------------------------------------------------------------
  // Private Method that is used when parsing addtile Command
  // @param input is third Parameter of a Command which includes requested Shape
  // @return Returns requied Enum Shape when Parse is sucessfull
  //
  static TileTypeLib::Shape parseTileTypeShape(const std::string& input);

  //--------------------------------------------------------------------------
  // Private Method that is used when parsing any Command
  // @param input is the unmodified Command Input String
  // @return Returns modified Command Input String in lowercase only
  //
  static std::string lowerChars(const std::string& input);

public:

  //--------------------------------------------------------------------------
  // Public Method responsible to parse all kind of Commands
  // @param command_string is the pure Command Input String
  // @return Returns different Shared Pointer depends on Command
  //
  static std::shared_ptr<CommandLib::Command> parseCommand(
      const std::string& command_string);

  //--------------------------------------------------------------------------
  // Public Method responsible to parse number of Arguments and Correctness
  // @param int argc is Number of Arguments
  // @param char* argv [] is a Char Pointer Array to Argument Strings
  // @return Shared Pointer of created StartGameCommand Object
  //
  static std::shared_ptr<CommandLib::Command> parseArguments(
      int argc, char* argv[]);
};

#endif // PARSER_H
