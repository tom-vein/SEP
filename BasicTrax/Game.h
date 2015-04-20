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
    std::array<Player, 2> players_;
    State state_ = State::NOTHING;
    Player& active_player_;
  public:
    Game(const std::array<Player, 2>& players);
    void tooglePlayer(); //reset num_of_placed_tiles_in_current_turn_ to 0
    State getState() const;
    void setState(State state);
    TilePtr getTileByPosition(const Position& position, int offset_x = 0, int offset_y = 0) const
      throw(InvalidPositionException);
    void removeTileAtPosition(const Position& position)
      throw(InvalidPositionException);
    void removeTile(TilePtr tile_to_remove);
    std::map<TileTypeLib::Edge, TilePtr> getTouchingTiles(const Position& position, Color color = Color::NONE, int offset_x = 0, int offset_y = 0) const;
    std::map<TileTypeLib::Edge, Color> getTouchingColors(const Position& position, Color color = Color::NONE, int offset_x = 0, int offset_y = 0) const;
    std::vector<Position> getEmptyPositionsAround(const Position& position, int offset_x = 0, int offset_y = 0) const;
    void addTile(TilePtr toAdd)
      throw(NoTilesLeftException);
    std::vector<TilePtr> getLastPlacedTiles() const;
    const Player& getActivePlayer() const;
    const Player& getPausedPlayer() const;
    int getMaxXValue() const;
    int getMinXValue() const;
    int getMaxYValue() const;
    int getMinYValue() const;
  };
}

#endif // GAME_H
