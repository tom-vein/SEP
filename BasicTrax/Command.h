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

class GameBoard;

namespace CommandLib
{
  enum class Code
  {
    QUIT, WIN, DRAW, CONTINUE
  };

  const Command readCommand(); //Use the parser class for this method

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

    virtual Code execute(GameBoard& game_board) = 0;

    //--------------------------------------------------------------------------
    // Getter Methods
    const std::string& getName() const;
  };

}

#endif //COMMAND_H_INCLUDED
