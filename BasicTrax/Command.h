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

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "GameBoard.h"

namespace CommandLib
{
  class Command;

  enum class Code
  {
    START, QUIT, WIN, DRAW, CONTINUE
  };

  //Use the parser class for this method
  //Output of sep>
  //Parse the Command with the parser
  //Return command
  std::shared_ptr<Command> readCommand(const GameLib::Game& game);

  class Command
  {
  public:
    Command() = default;

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
    const std::vector<std::string>& getParams() const;
  };

  class StartGameCommand : public Command
  {
  private:
    std::string file_name_;
  public:
    StartGameCommand(const std::string& file_name);
    virtual Code execute(GameBoard& game_board) const override;
    virtual ~StartGameCommand() override;
    const std::string& getFileName() const;
  };

  class DoTurnCommand : public Command
  {
  private:
    TilePtr tile_;
  public:
    DoTurnCommand(TilePtr tile);
    virtual Code execute(GameBoard& game_board) const override;
    virtual ~DoTurnCommand() override;
  };

  class QuitCommand : public Command
  {
  public:
    virtual Code execute(GameBoard& game_board) const override;
    virtual ~QuitCommand() override;
  };

  class ErrorCommand : public Command
  {
  private:
    std::string message_;
  public:
    ErrorCommand(std::string message);
    virtual Code execute(GameBoard&) const override;
    virtual ~ErrorCommand() override;
  };

  class WriteCommand : public Command
  {
  private:
    std::string file_name_;
  public:
    WriteCommand(std::string file_name);
    virtual Code execute(GameBoard&) const override;
    virtual ~WriteCommand() override;
  };
}

#endif //COMMAND_H_INCLUDED
