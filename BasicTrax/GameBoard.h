#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "FileManager.h"
#include "Game.h"
#include "Exceptions.h"
#include <set>


class GameBoard
{
private:
  GameLib::Game game_;
  FileManager file_manager_; //Before writing look if should_write_to_file_ is
  //set to true

  std::vector<TilePtr> tried_insertions_; // used for rollback when invalid move would be made
  bool should_write_to_file_;

  void doForcedPlay(TilePtr last_placed);
  bool checkWin();
  bool canTileBePlaced(TilePtr tile_to_check) //are colors of edges correct
  throw(InvalidPositionException);
  bool canTileBePlaced(std::map<TileTypeLib::Edge, TilePtr> touching_tiles, TilePtr tile_to_check);
  bool checkTwoTiles(TilePtr first, TilePtr second, TileTypeLib::Edge touching_edge_of_second_tile);

  class WinnerChecker
  {
  public:
    enum class LineDirection {UP, DOWN, LEFT, RIGHT, NONE};
    const Player& determineWinner(const GameLib::Game& game) const;
  private:
    const unsigned int MIN_LENGTH_OF_WINNING_LINE = 8;

    bool hasPlayerWon(const Player& player,
                      const GameLib::Game& game) const;
    bool isLoop(Color player_color, TilePtr start_tile, TilePtr previous_tile,
                TilePtr current_tile, const GameLib::Game& game) const;
    bool isLineLongEnough(Color player_color, TilePtr start_tile,
                          const GameLib::Game& game) const;
    LineDirection isLineLongEnough(Color player_color, TilePtr previous_tile,
                                   TilePtr current_tile,
                                   const GameLib::Game& game,
                                   std::set<int>& x_values_of_line,
                                   std::set<int>& y_values_of_line) const;
    LineDirection determineDirectionOfFreeEdge(Color color, TilePtr tile,
                                               const GameLib::Game& game) const;
    TilePtr determineNextTile(Color player_color, TilePtr previous_tile,
                              TilePtr current_tile,
                              const GameLib::Game& game) const;
  };

public:
  GameBoard(const GameLib::Game& game, const std::string& file_name);
  void startGame();
  void doTurn(TilePtr tile)
  throw(InvalidPositionException);
};

#endif // GAMEBOARD_H
