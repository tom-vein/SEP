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
  private:
    enum class LineDirection {UP, DOWN, LEFT, RIGHT, NONE};

    class LineWinningCriteria
    {
    private:
      const unsigned int MIN_LENGTH_OF_WINNING_LINE = 8;
      std::set<int> x_values_of_line_;
      std::set<int> y_values_of_line_;
      LineDirection direction_of_first_end_ = LineDirection::NONE;
      LineDirection direction_of_second_end_ = LineDirection::NONE;
      bool first_end_outmost_edge_ = false;
      bool second_end_other_outmost_edge_ = false;
    public:
      void addXValue(int x);
      void addYValue(int y);
      void setDirectionOfFirstEnd(LineDirection direction_of_first_end);
      void setDirectionOfSecondEnd(LineDirection direction_of_second_end);
      void setFirstEndOutmostEdge(bool first_end_outmost_edge);
      void setSecondEndOtherOutmostEdge(bool second_end_other_outmost_edge);
      bool allWinningCriteriaFulfilled() const;
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
    void analyseLineEnd(LineWinningCriteria& line_winning_criteria,
                         Color color, TilePtr tile,
                         const GameLib::Game& game) const;
    LineDirection determineDirectionOfFreeEdge(Color color, TilePtr tile,
                                               const GameLib::Game& game) const;
    std::vector<TilePtr> determineNextTiles(Color player_color,
                                            TilePtr previous_tile,
                                            TilePtr current_tile,
                                            const GameLib::Game& game) const;
  public:
    const Player& determineWinner(const GameLib::Game& game) const;
  };

public:
  GameBoard(const GameLib::Game& game, const std::string& file_name);
  void startGame();
  void doTurn(TilePtr tile)
  throw(InvalidPositionException);
};

#endif // GAMEBOARD_H
