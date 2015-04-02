#ifndef GAME_H
#define GAME_H

#include <vector>
#include <array>
#include "Tile.h"
#include "Player.h"

class Game
{
private:
  static const unsigned int MAX_OF_TILES = 64;
  std::vector<Tile> tiles_(MAX_OF_TILES);
  std::array<Player, 2> players_;
  bool running_ = false;
  Player active_player_;
public:
  Game(std::array<Player, 2> players);
  void tooglePlayer();
  bool isRunning() const;
  bool setRunning(bool running);
};

#endif // GAME_H
