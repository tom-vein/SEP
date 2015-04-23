//------------------------------------------------------------------------------
// main.cpp
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Parser.h"
#include "Command.h"
#include "GameBoard.h"
#include "Exit.h"

//------------------------------------------------------------------------------
// main function
// entry point for execution
// @param argc argument count
// @param **argv argument values
// @return return value for the OS
//
int main(int argc, char* argv[])
{
  std::shared_ptr<CommandLib::Command> command;
  std::shared_ptr<CommandLib::StartGameCommand> start_game_command;
  Player player1(Color::WHITE);
  Player player2(Color::RED);

  std::array<Player, 2>players{player1, player2};

  GameLib::Game game(players);

  try
  {
    command = Parser::parseArguments(argc, argv);
  }
  catch(WrongUsageProgramException& ex)
  {
    std::cout << ex.what() << std::endl;
    return static_cast<int>(Exit::Code::WRONG_USAGE);
  }

  start_game_command =
      std::dynamic_pointer_cast<CommandLib::StartGameCommand>(command);

  TileTypeLib::TileType::initTileTypes();

  GameBoard game_board(game, start_game_command->getFileName());
  CommandLib::Code current_code;
  try
  {
    while((current_code = command->execute(game_board)) !=
          CommandLib::Code::QUIT)
    {
      if(current_code == CommandLib::Code::DRAW)
      {
        std::cout << "No more tiles left. Game ends in a draw!" << std::endl;
        break;
      }

      if(current_code == CommandLib::Code::WIN)
      {
        std::cout << "Player " << game_board.getWinner() << " wins!";
        std::cout << std::endl;
        break;
      }

      do
      {
        try
        {
          command = CommandLib::readCommand();
        }
        catch(WrongParameterException& e)
        {
          std::cout << e.what() << std::endl;
          command = nullptr;
        }

      }
      while(!command);
    }
    std::cout << "Bye!" << std::endl;
    return static_cast<int>(Exit::Code::SUCCESS);
  }
  catch(std::bad_alloc)
  {
    //TODO: Constant
    std::cout << "Error: Out of Memory!" << std::endl;
    return static_cast<int>(Exit::Code::OUT_OF_MEMORY);
  }
}

