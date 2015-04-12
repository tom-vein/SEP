#ifndef GAME_H
#define GAME_H

#include <vector>
#include <array>
#include "Tile.h"
#include "Player.h"

namespace GameLib
{
  enum class State
  {
    NOTHING,
    RUNNING,
    DRAW,
    WIN
  };

  class Game
  {
  private:
    static const unsigned int MAX_OF_TILES = 64;
    std::vector<Tile> tiles_;
    std::array<PlayerLib::Player, 2> players_;
    State state_ = State::NOTHING;
    PlayerLib::Player& active_player_;
  public:
    Game(const std::array<PlayerLib::Player, 2>& players);
    void tooglePlayer();
    State getState() const;
    void setState(State state);
    const Tile& getTile(const Position& position);
  };
}

#endif // GAME_H
