//------------------------------------------------------------------------------
// GameBoard.h
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "FileManager.h"
#include "Game.h"
#include "Exceptions.h"
#include <set>
#include <iostream>

//----------------------------------------------------------------------------
// Gameboard Class
// used for checking if any player has won, writing to files and checking if a
// tile addtile-command is correct
//
class GameBoard
{
private:

  //----------------------------------------------------------------------------
  // Result checker Class
  // Used for checking if any player has won
  //
  class ResultChecker
  {
  private:

    //----------------------------------------------------------------------------
    // Class for encapsulating checks regarding winning criterias
    //
    class LineWinningCriteria
    {
    private:
      //TODO: enum comment?
      enum class LineDirection {UP, DOWN, LEFT, RIGHT, NONE};

      //----------------------------------------------------------------------------
      // Constant indicating how long a line has to be in order to win the game
      //
      static const unsigned int MIN_LENGTH_OF_WINNING_LINE;

      //TODO: comment
      std::set<int> x_values_of_line_;
      std::set<int> y_values_of_line_;
      LineDirection direction_of_first_end_ = LineDirection::NONE;
      LineDirection direction_of_second_end_ = LineDirection::NONE;
      Position position_of_first_end_{0, 0};
      Position position_of_second_end_{0, 0};

      //TODO: comment
      LineDirection determineDirectionOfFreeEdge(Color color, TilePtr tile,
                                                 const GameLib::Game& game)
                                                 const;
    public:
      void addXValue(int x);
      void addYValue(int y);
      void analyseLineEnd(Color color, TilePtr tile, const GameLib::Game& game);
      bool allWinningCriteriaFulfilled(const GameLib::Game& game) const;
    };

    //----------------------------------------------------------------------------
    // method used for checking if the given player has won
    // @param Player which should be checked
    // @param reference to instance of game
    // @return true if player has won, otherwise false
    //
    bool hasPlayerWon(const Player& player,
                      const GameLib::Game& game) const;

    //TODO: comment
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
    //----------------------------------------------------------------------------
    // method used for retrieving the color of the player which has won
    // @param reference to instance of game
    // @return returns the color of a player, if a player has won. otherwise
    //  it returns Color::NONE
    //
    Color determineWinner(const GameLib::Game& game) const;

    //----------------------------------------------------------------------------
    // method used for checking if the current situation is a draw
    // @param reference to instance of game
    // @return true game situation is a draw, otherwise false
    //
    bool isDraw(const GameLib::Game& game) const;
  };

  //----------------------------------------------------------------------------
  // Instance of game for adding tiles ect
  //
  GameLib::Game game_;

  //----------------------------------------------------------------------------
  // Instance of the filemanager for writing to files
  //
  FileManager file_manager_;

  //----------------------------------------------------------------------------
  // Instance of resultChecker for checking winning criteria
  //
  ResultChecker result_checker_;

  //----------------------------------------------------------------------------
  // Member for holding the color of the winner, if any exists
  //
  Color winner_ = Color::NONE;

  //----------------------------------------------------------------------------
  // vector used for temporary saving insertions which took place in one turn
  //
  std::vector<TilePtr> tried_insertions_;

  //----------------------------------------------------------------------------
  // member indication if the game was started in the graphical mode
  //
  bool should_write_to_file_;

  //----------------------------------------------------------------------------
  // Method for automatically adding all clearly defined tiles
  // @param std::shared_ptr<Tile> pointing to the tile which was last placed
  //
  void doForcedPlay(TilePtr last_placed);

  //----------------------------------------------------------------------------
  // method used for checking if anybody has won
  // @return returns true if a player has won, otherwise returns flase
  //
  bool checkWin();

  //----------------------------------------------------------------------------
  // Method used for checking if it is okay to place a tile
  // @param map containing all tiles which touch the positing of the tile
  // @param std::shared_ptr<Tile> pointing to the tile which should be checked
  // @return returns true if tile can be placed, otherwise exception is thrown
  //
  bool canTileBePlaced(std::map<TileTypeLib::Edge, TilePtr> touching_tiles,
                       TilePtr tile_to_check);
  //----------------------------------------------------------------------------
  // Method used for checking if the edges of two touching tiles match
  // @param pointer to tile which should be checked
  // @param pointer to tile which is alredy placed and touches first tile
  // @param touching Edge (perspecitve of tile which should be checked)
  // @return returns true if colors match, otherwise returns flase
  //
  bool checkTwoTiles(TilePtr tile_to_check, TilePtr other,
                     TileTypeLib::Edge touching_edge_of_tile_to_check);

public:
  //----------------------------------------------------------------------------
  // Constructor
  //
  GameBoard(const GameLib::Game& game, const std::string& file_name);

  //----------------------------------------------------------------------------
  // Method used for trying to add a tile to the gameboard
  // @param Position on which the tile should be placed
  // @param Shape of the tile which should be placed
  //
  void doTurn(const Position& position, TileTypeLib::Shape shape);

  //----------------------------------------------------------------------------
  // Method indicating if the situation is a draw
  // @return returns true if game situation is a draw, otherwise false
  //
  bool isDraw() const;

  //----------------------------------------------------------------------------
  // Method indicating if the game has a winner
  // @return returns true if game situation has a winner, otherwise false
  //
  bool hasWinner() const;

  //----------------------------------------------------------------------------
  // Getter for returning the color of the winner as string
  // @return returns color of the winner as string, or "no winner" if there is
  //  no winner
  //
  std::string getWinner() const;

  //----------------------------------------------------------------------------
  // Method used for writing the gameboard to a file
  // @param Filename (default is no filename)
  //
  void write(const std::string& file_name = "");
};

#endif // GAMEBOARD_H
