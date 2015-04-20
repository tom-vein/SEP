#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Parser.h"
#include "Command.h"
#include "GameBoard.h"

int main(int argc, char* argv[])
{
  std::string arguments;
  std::shared_ptr<CommandLib::Command> command;
  std::shared_ptr<CommandLib::StartGameCommand> start_game_command;
  Player player1(Color::RED);
  Player player2(Color::WHITE);

  std::array<Player, 2>players{player1, player2};

  GameLib::Game game(players);

  arguments = Parser::parseArguments(argc, argv);
  command = Parser::parseCommand(arguments, game);


  //Check if this comparison works
  if(typeid(command) != typeid(CommandLib::StartGameCommand))
    std::cout << "throw an appropriate exception here" << std::endl;

  start_game_command =
     std::dynamic_pointer_cast<CommandLib::StartGameCommand>(command);

  TileTypeLib::TileType::initTileTypes();

  GameBoard game_board(game, start_game_command->getFileName());

  while(command->execute(game_board) != CommandLib::Code::QUIT)
  {
    command = CommandLib::readCommand(game);
  }


  return 0;
}

