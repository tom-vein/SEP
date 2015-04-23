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

  enum class Code
  {
    START,
    QUIT,
    WIN,
    DRAW,
    CONTINUE
  };


  //--------------------------------------------------------------------------
  // Method reads command from commandline and generates a pointer to a
  // Command object
  // @return returns shared_ptr to a command-object
  //
  std::shared_ptr<Command> readCommand();

  //--------------------------------------------------------------------------
  // Class Command
  // Represents a single comman
  //
  class Command
  {
  public:
    //--------------------------------------------------------------------------
    // deleted constructor
    //
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

  //--------------------------------------------------------------------------
  // Command used for starting adding a tile to a gameboard
  //
  class DoTurnCommand : public Command
  {
  private:
    //--------------------------------------------------------------------------
    // Position of the tile that should be placed
    //
    Position position_;

    //--------------------------------------------------------------------------
    // Shape of the tile which should be placed
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

  //--------------------------------------------------------------------------
  // Command used for quitting the game
  //
  class QuitCommand : public Command
  {
  public:
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


  //--------------------------------------------------------------------------
  // Command used for writing the gameboard to a file
  //
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
