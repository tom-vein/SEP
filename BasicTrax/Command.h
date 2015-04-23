//------------------------------------------------------------------------------
// Command.h
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

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

  //----------------------------------------------------------------------------
  // Color Class
  // list of Enums to set the correct Program State
  //
  enum class Code
  {
    START, QUIT, WIN, DRAW, CONTINUE
  };

  //Use the parser class for this method
  //Output of sep>
  //Parse the Command with the parser
  //Return command
  std::shared_ptr<Command> readCommand();

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
    // @param game_board The board where action should be performed on
    // @return Code representing the state of the game

    virtual Code execute(GameBoard& game_board) const = 0;

    //--------------------------------------------------------------------------
    // Getter Methods
    const std::vector<std::string>& getParams() const;
  };

  class StartGameCommand : public Command
  {
  private:
    //--------------------------------------------------------------------------
    // Name of the file that should be written
    //
    std::string file_name_;
  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    StartGameCommand(const std::string& file_name);

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param game_board The board where action should be performed on
    // @return Code representing the state of the game
    virtual Code execute(GameBoard& game_board) const override;

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~StartGameCommand() override;

    //--------------------------------------------------------------------------
    // Getter
    //
    const std::string& getFileName() const;
  };

  class DoTurnCommand : public Command
  {
  private:
    Position position_;
    TileTypeLib::Shape shape_;
  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    DoTurnCommand(const Position& position, TileTypeLib::Shape shape);

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param game_board The board where action should be performed on
    // @return Code representing the state of the game
    virtual Code execute(GameBoard& game_board) const override;

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~DoTurnCommand() override;
  };

  class QuitCommand : public Command
  {
  public:
    //QuitCommand();

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param game_board The board where action should be performed on
    // @return Code representing the state of the game
    virtual Code execute(GameBoard& game_board) const override;

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~QuitCommand() override;
  };

  class ErrorCommand : public Command
  {
  private:
    //--------------------------------------------------------------------------
    // Error message that should be displayed
    //
    std::string message_;
  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    ErrorCommand(std::string message);

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param game_board The board where action should be performed on
    // @return Code representing the state of the game
    virtual Code execute(GameBoard&) const override;

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~ErrorCommand() override;
  };

  class WriteCommand : public Command
  {
  private:
    //--------------------------------------------------------------------------
    // Name of the file that should be written
    //
    std::string file_name_;
  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    WriteCommand(std::string file_name);

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param game_board The board where action should be performed on
    // @return Code representing the state of the game
    virtual Code execute(GameBoard&) const override;

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~WriteCommand() override;
  };
}

#endif //COMMAND_H_INCLUDED
