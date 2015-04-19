#ifndef GAME_H
#define GAME_H

#include <vector>
#include <array>
#include <map>
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
  enum class RelativePosition
  {
    LEFT,
    TOP,
    RIGHT,
    BOTTOM,
  };

  class Game
  {
  private:
    static const unsigned int MAX_OF_TILES = 64;
    unsigned int num_of_placed_tiles_in_current_turn_ = 0;
    std::vector<TilePtr> tiles_;
    std::array<PlayerLib::Player, 2> players_;
    State state_ = State::NOTHING;
    PlayerLib::Player& active_player_;
  public:
    Game(const std::array<PlayerLib::Player, 2>& players);
    void tooglePlayer(); //reset num_of_placed_tiles_in_current_turn_ to 0
    State getState() const;
    void setState(State state);
    TilePtr getTileByPosition(const Position& position, int offset_x = 0, int offset_y = 0)
      throw(InvalidPositionException);
    void removeTileAtPosition(const Position& position)
      throw(InvalidPositionException);
    void removeTile(TilePtr tile_to_remove);
    std::map<TileTypeLib::Edge, TilePtr> getTouchingTiles(const Position& position, int offset_x = 0, int offset_y = 0);
    std::map<TileTypeLib::Edge, TileTypeLib::Color> getTouchingColors(const Position& position, int offset_x = 0, int offset_y = 0);
    std::vector<Position> getEmptyPositionsAround(const Position& position, int offset_x = 0, int offset_y = 0);
    void addTile(TilePtr toAdd)
      throw(NoTilesLeftException);
    unsigned int getNumOfPlacedTilesInCurrentTurn() const;
  };
}

#endif // GAME_H
