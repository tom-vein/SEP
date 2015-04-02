//------------------------------------------------------------------------------
// Filename: Command.h
// Description: Class representing a general command
// Authors: Tutors
// Tutor: Tutors
// Group: 42
// Created: 08.08.2011
// Last change: 02.09.2011
//------------------------------------------------------------------------------

#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <vector>
#include <memory>
#include "Command.h"

class GameBoard;

namespace CommandLib
{
  class Command;

  enum class Code
  {
    QUIT, WIN, DRAW, CONTINUE
  };

  //Use the parser class for this method
  //Output of sep>
  //Parse the Command with the parser
  //Return command
  std::unique_ptr<Command> readCommand();

  class Command
  {
  private:
    //--------------------------------------------------------------------------
    /// Name of this command
    std::string command_name_;

    std::vector<std::string> params;

  public:
    //--------------------------------------------------------------------------
    // Constructor

    Command(std::string name);

    //--------------------------------------------------------------------------
    // Deleted copy constructor

    Command(const Command& original) = delete;

    //--------------------------------------------------------------------------
    // Deleted assignment operator

    Command& operator=(const Command& original) = delete;

    //--------------------------------------------------------------------------
    // Destructor

    virtual ~Command();

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action

    virtual Code execute(GameBoard& game_board) const = 0;

    //--------------------------------------------------------------------------
    // Getter Methods
    const std::string& getName() const;
    const std::vector<std::string> getParams() const;
  };

}

#endif //COMMAND_H_INCLUDED
