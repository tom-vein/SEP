#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "FileManager.h"
#include "Game.h"
#include "Exceptions.h"
#include <set>


class GameBoard
{
private:
  class ResultChecker
  {
  private:
    class LineWinningCriteria
    {
    private:
      enum class LineDirection {UP, DOWN, LEFT, RIGHT, NONE};

      const unsigned int MIN_LENGTH_OF_WINNING_LINE = 8;
      std::set<int> x_values_of_line_;
      std::set<int> y_values_of_line_;
      LineDirection direction_of_first_end_ = LineDirection::NONE;
      LineDirection direction_of_second_end_ = LineDirection::NONE;
      Position position_of_first_end_{0, 0};
      Position position_of_second_end_{0, 0};

      LineDirection determineDirectionOfFreeEdge(Color color, TilePtr tile,
                                                 const GameLib::Game& game) const;
    public:
      void addXValue(int x);
      void addYValue(int y);
      void analyseLineEnd(Color color, TilePtr tile, const GameLib::Game& game);
      bool allWinningCriteriaFulfilled(const GameLib::Game& game) const;
    };

    bool hasPlayerWon(const Player& player,
                      const GameLib::Game& game) const;
    bool isLoop(Color player_color, TilePtr start_tile, TilePtr previous_tile,
                TilePtr current_tile, const GameLib::Game& game,
                bool start_of_recursion = true) const;
    bool doesLineWin(Color player_color, TilePtr start_tile,
                     const GameLib::Game& game) const;
    void checkIfLineWins(Color player_color, TilePtr previous_tile,
                         TilePtr current_tile, const GameLib::Game& game,
                         LineWinningCriteria& line_winning_criteria,
                         bool start_of_recursion = true) const;
    std::vector<TilePtr> determineNextTiles(Color player_color,
                                            TilePtr previous_tile,
                                            TilePtr current_tile,
                                            const GameLib::Game& game) const;
  public:
    const Player& determineWinner(const GameLib::Game& game) const;
    bool isDraw(const GameLib::Game& game) const;
  };

  GameLib::Game game_;
  FileManager file_manager_; //Before writing look if should_write_to_file_ is
  ResultChecker result_checker_;

  std::vector<TilePtr> tried_insertions_; // used for rollback when invalid move would be made
  bool should_write_to_file_;

  void doForcedPlay(TilePtr last_placed);
  bool checkWin();
  bool canTileBePlaced(TilePtr tile_to_check) //are colors of edges correct
  throw(InvalidPositionException);
  bool canTileBePlaced(std::map<TileTypeLib::Edge, TilePtr> touching_tiles, TilePtr tile_to_check);
  bool checkTwoTiles(TilePtr first, TilePtr second, TileTypeLib::Edge touching_edge_of_second_tile);

public:
  GameBoard(const GameLib::Game& game, const std::string& file_name);
  void startGame();
  void doTurn(TilePtr tile)
  throw(InvalidPositionException);
};

#endif // GAMEBOARD_H
