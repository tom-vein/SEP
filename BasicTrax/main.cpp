#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Parser.h"
#include "Command.h"
#include "GameBoard.h"

int main(int argc, char* argv[])
{
  std::shared_ptr<CommandLib::Command> command;
  std::shared_ptr<CommandLib::StartGameCommand> start_game_command;
  Player player1(Color::RED);
  Player player2(Color::WHITE);

  std::array<Player, 2>players{player1, player2};

  GameLib::Game game(players);

  try
  {
    command = Parser::parseArguments(argc, argv);
  }
  catch(WrongUsageProgramException& ex)
  {
    std::cout << ex.what();
    return 2;
  }

  //Check if this comparison works
//  if(typeid(command) != typeid(CommandLib::StartGameCommand))
//    throw InappropriateCommandException("the command here is inappropriate");

  start_game_command =
      std::dynamic_pointer_cast<CommandLib::StartGameCommand>(command);

  TileTypeLib::TileType::initTileTypes();

  GameBoard game_board(game, start_game_command->getFileName());
  CommandLib::Code current_code;
  try
  {
    while((current_code = command->execute(game_board)) != CommandLib::Code::QUIT)
    {
      if(current_code == CommandLib::Code::DRAW)
      {
        std::cout << "No more tiles left. Game ends in a draw!" << std::endl;
        break;
      }

      if(current_code == CommandLib::Code::WIN)
      {
        std::cout << "Player " << game_board.getWinner() << " wins!" << std::endl;
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
    return 0;
  }
  catch(std::bad_alloc)
  {
    std::cout << "Error: Out of Memory!\n";
    return 1;
  }
}

