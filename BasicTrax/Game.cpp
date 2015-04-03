#include "Game.h"

GameLib::Game::Game(const std::array<PlayerLib::Player, 2>& players) :
  players_(players), active_player_(players_.at(0))
{

}
