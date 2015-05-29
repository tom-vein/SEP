//------------------------------------------------------------------------------
// Game.h
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

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
  //----------------------------------------------------------------------------
  // State Class
  // list of Enums to track the Program State
  //
  enum class State
  {
    NOTHING,
    RUNNING,
    DRAW,
    WIN
  };

  //----------------------------------------------------------------------------
  // Game class
  // Encapsulates all tiles and the players
  //
  class Game
  {
  private:

    //--------------------------------------------------------------------------
    // Constant which indicates the maximum number of tiles
    //
    static const unsigned int MAX_OF_TILES = 64;

    //--------------------------------------------------------------------------
    // Logs the number of all placed tiles in the current turn. This includes
    // the tile that the active player places and the tiles that are placed
    // by forced play
    //
    unsigned int num_of_placed_tiles_in_current_turn_ = 0;

    //--------------------------------------------------------------------------
    // Vector holding all tiles
    //
    std::vector<TilePtr> tiles_;

    //--------------------------------------------------------------------------
    // array with all players
    //
    std::array<Player, 2> players_;

    //--------------------------------------------------------------------------
    // Current state of the game
    //
    State state_ = State::NOTHING;

    //--------------------------------------------------------------------------
    // Reference to the player whichs turn it is to add a tile
    //
    Player& active_player_;

    //--------------------------------------------------------------------------
    // Checks if there are empty places around this tile
    //
    bool hasEmptyPositions(Position position) const;

    //--------------------------------------------------------------------------
    // Checks if the Tile has this position
    //
    //bool hasPosition(TilePtr tile);

    //mutable Position position_to_return;

  public:

    //--------------------------------------------------------------------------
    // Constructor
    //
    Game(const std::array<Player, 2>& players);

    //--------------------------------------------------------------------------
    // Toggles the active player
    //
    void tooglePlayer();

    //--------------------------------------------------------------------------
    // Getter
    // @return current state of the game
    //
    State getState() const;

    //--------------------------------------------------------------------------
    // Setter
    // @param state State which the game should have
    //
    void setState(State state);

    //--------------------------------------------------------------------------
    // Method for retrieving a tile whichs position is known
    // @param position const reference to position of the wanted tile
    // @param offset_x offset in x-direction relative to position (default = 0)
    // @param offset_y offset in y-direction relative to position (default = 0)
    // @return Returns a std::shared_ptr<Tile> pointing to the wanted tile
    //         or nullptr if no tile is at this position
    //
    TilePtr getTileByPosition(Position position,
                              int offset_x = 0, int offset_y = 0) const;

    //--------------------------------------------------------------------------
    // Method for deleting a tile at the position
    // @param position Position of tile which should be deleted
    //
    void removeTileAtPosition(const Position& position)
    throw(InvalidPositionException);

    //--------------------------------------------------------------------------
    // Method for deleting a certain tile
    // @param tile_to_remove std::shared_ptr<Tile> pointing to Tile which should
    //                       be deleted
    //
    void removeTile(TilePtr tile_to_remove);

    //--------------------------------------------------------------------------
    // Getter for retrieving a map consisting of a edge as key and
    // shared_ptr<Tile> as value of Tiles which touch the given position
    // @param position Position of which all touching tiles are wanted
    // @param color Returns only touching tiles that are next to the edge
    //              of the passed color. If the passed color is NONE
    //              all touching tiles will be returned (default = NONE)
    // @param offset_x offset in x-direction relative to position (default = 0)
    // @param offset_y offset in y-direction relative to position (default = 0)
    // @return returns map contaning edge and tileptr of touching tiles
    //
    std::map<TileTypeLib::Edge, TilePtr> getTouchingTiles(
        const Position& position, Color color = Color::NONE,
        int offset_x = 0, int offset_y = 0) const;

    //--------------------------------------------------------------------------
    // Getter for retrieving a map containing a edge as key and
    // Color of this edge (seen of perspective of tile as <position> as value
    // of which touch the given position
    // @param position Position of which all touching colors are wanted
    // @param offset_x offset in x-direction relative to position (default = 0)
    // @param offset_y offset in y-direction relative to position (default = 0)
    // @return returns map contaning edge and color of touching edges
    //
    std::map<TileTypeLib::Edge, Color> getTouchingColors(
        const Position& position, int offset_x = 0, int offset_y = 0) const;

    //--------------------------------------------------------------------------
    // Getter for retrieving a vector of positions, which have no tile but are
    // next to <postion>
    // @param position Position of which all touching tiles are wanted
    // @param offset_x offset in x-direction relative to position (default = 0)
    // @param offset_y offset in y-direction relative to position (default = 0)
    // @return returns vector of positions which are empty but touch <position>
    //
    std::vector<Position> getEmptyPositionsAround(
        const Position& position, int offset_x = 0, int offset_y = 0) const;


    //--------------------------------------------------------------------------
    // Method for adding a tile to the gameboard
    // @param tile_to_add std::shared_ptr<Tile> pointing to Tile which should be
    //                    added
    //
    void addTile(TilePtr tile_to_add);

    //--------------------------------------------------------------------------
    // Returns all tiles that have been placed during the current turn
    // (including them who where placed by forced play)
    std::vector<TilePtr> getLastPlacedTiles() const;

    //--------------------------------------------------------------------------
    // This method returns the touching edge between two Tiles
    TileTypeLib::Edge getTouchingEdge (Position first, Position second) const;

    //--------------------------------------------------------------------------
    // Returns all Tiles with at least one empty position around
    std::vector<TilePtr> getAllEdges() const;

    //--------------------------------------------------------------------------
    // resets num_of_placed_tiles_in_current_turn_ to 0
    void resetNumOfPlacedTilesInCurrentTurn()
    {
      num_of_placed_tiles_in_current_turn_ = 0;
    }

    //--------------------------------------------------------------------------
    // Getter methods
    //
    const Player& getActivePlayer() const;
    const Player& getPausedPlayer() const;
    int getMaxXValue() const;
    int getMinXValue() const;
    int getMaxYValue() const;
    int getMinYValue() const;
    unsigned int getTileCount() const;
    static unsigned int getMaxOfTiles();
    unsigned int getTilesSize() {return tiles_.size();}
  };
}

#endif // GAME_H
