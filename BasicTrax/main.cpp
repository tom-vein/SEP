#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Parser.h"
#include "Command.h"
#include "GameBoard.h"

int main(int argc, char* argv[])
{
  std::vector<std::string> params;
  std::string arguments = Parser::parseArguments(argc, argv);
  std::unique_ptr<CommandLib::Command> command =
      Parser::parseCommand(arguments);

  //check if the command is an StartGameCommand

  TileTypeLib::TileType::initTileTypes();

  PlayerLib::Player player1(PlayerLib::Color::RED);
  PlayerLib::Player player2(PlayerLib::Color::WHITE);

  std::array<PlayerLib::Player, 2>players{player1, player2};

  GameLib::Game game(players);

  GameBoard game_board(game);

  while(command->execute(game_board) == CommandLib::Code::CONTINUE)
  {
    command = CommandLib::readCommand();
  }

  return 0;
}

