#include <iostream>
#include "Game.h"
#include "Player.h"

int main(int argc, char* argv[])
{
  std::array<Player, 2>players;

  Player player1(Color::RED);
  Player player2(Color::WHITE);
  players.at(0) = player1;
  players.at(1) = player2;

  Game game(players);

  return 0; //test
}

