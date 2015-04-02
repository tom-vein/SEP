#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Parser.h"
#include "Command.h"
#include "GameBoard.h"

int main(int argc, char* argv[])
{
  std::string arguments;
  CommandLib::Command command;
  std::vector<std::string> params;

  arguments = Parser::parseArguments(argc, argv);
  command = Parser::parseCommand(arguments);

  //check if the command is an StartGameCommand

  std::array<Player, 2>players;

  Player player1(Color::RED);
  Player player2(Color::WHITE);
  players.at(0) = player1;
  players.at(1) = player2;

  Game game(players);

  GameBoard game_board(game);

  while(command.execute(game_board) == CommandLib::Code::CONTINUE)
  {
    command = CommandLib::readCommand();
  }

  return 0;
}

