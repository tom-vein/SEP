#ifndef GAME_H
#define GAME_H

#include <vector>
#include <array>
#include "Tile.h"
#include "Player.h"
#include "Exceptions.h"

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
    std::vector<std::shared_ptr<Tile>> tiles_;
    std::array<PlayerLib::Player, 2> players_;
    State state_ = State::NOTHING;
    PlayerLib::Player& active_player_;
  public:
    Game(const std::array<PlayerLib::Player, 2>& players);
    void tooglePlayer();
    State getState() const;
    void setState(State state);
    std::shared_ptr<Tile> getTileByPosition(const Position& position, int offset_x = 0, int offset_y = 0)
      throw(InvalidPositionException);
    void removeTileAtPosition(const Position& position)
      throw(InvalidPositionException);
    void removeTile(std::shared_ptr<Tile> tile_to_remove);
    const std::vector<std::shared_ptr<Tile>> getTouchingTiles(const Position& position);
  };
}

#endif // GAME_H
