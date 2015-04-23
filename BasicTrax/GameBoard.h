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

    //--------------------------------------------------------------------------
    // Class for encapsulating checks regarding winning criterias
    //
    class LineWinningCriteria
    {
    private:
      //------------------------------------------------------------------------
      // This enum is used to determine the direction of the line ends
      //
      enum class LineDirection {UP, DOWN, LEFT, RIGHT, NONE};

      //------------------------------------------------------------------------
      // Constant indicating how long a line has to be in order to win the game
      //
      static const unsigned int MIN_LENGTH_OF_WINNING_LINE = 8;

      //------------------------------------------------------------------------
      // x_values_of_line_ is used to check if there are enough tiles in order
      // to achieve a horizontal win
      //
      std::set<int> x_values_of_line_;

      //------------------------------------------------------------------------
      // y_values_of_line_ is used to check if there are enough tiles in order
      // to achieve a vertical win
      //
      std::set<int> y_values_of_line_;

      //------------------------------------------------------------------------
      // direction_of_first_end_ is needed to determine in which direction
      // the first end of the line points
      //
      LineDirection direction_of_first_end_ = LineDirection::NONE;

      //------------------------------------------------------------------------
      // direction_of_second_end_ is needed to determine in which direction
      // the second end of the line points
      //
      LineDirection direction_of_second_end_ = LineDirection::NONE;

      //------------------------------------------------------------------------
      // position_of_first_end_ is used to save the location of the first
      // end
      //
      Position position_of_first_end_{0, 0};

      //------------------------------------------------------------------------
      // position_of_second_end_ is used to save the location of the second
      // end
      //
      Position position_of_second_end_{0, 0};

      //------------------------------------------------------------------------
      // This method returns the direction to which the end of the line
      // points to. Therefore it just determines which edge of the passed
      // tile is free.
      //
      // @param color Edge color where could be a free edge
      // @param tile Tile that is used to termine the free edge
      // @param game The current game that takes place
      //
      LineDirection determineDirectionOfFreeEdge(Color color, TilePtr tile,
                                                 const GameLib::Game& game)
      const;
    public:
      //------------------------------------------------------------------------
      // This method is used to add a value to x_values_of_line_. No double
      // values will be added
      // @param x The value that is added
      //
      void addXValue(int x);

      //------------------------------------------------------------------------
      // This method is used to add a value to y_values_of_line_. No double
      // values will be added
      // @param y The value that is added
      //
      void addYValue(int y);

      //------------------------------------------------------------------------
      // This method analyses one line end and based on this data it sets
      // the variables direction_of_first_end_ and position_of_first_end_ or
      // the variables direction_of_second_end_ and position_of_second_end_
      // depending on what line end it is.
      // @param color The edge color that should be considered in analysing
      //              the line end
      // @param tile The line end that is analysed
      // @param game The current game that takes place
      //
      void analyseLineEnd(Color color, TilePtr tile, const GameLib::Game& game);

      //------------------------------------------------------------------------
      // This methode checks if all winning criteria are fulfilled and
      // returns true if this case occurs. Otherwise it returns false.
      // @param game The current game that takes place. This object is needed
      //             to carry out the check
      // @return returns true if all winning criteria are fulfilled. Otherwise
      //         false
      //
      bool allWinningCriteriaFulfilled(const GameLib::Game& game) const;
    };

    //--------------------------------------------------------------------------
    // method used for checking if the given player has won
    // @param player Player which should be checked
    // @param game reference to instance of game
    // @return true if player has won, otherwise false
    //
    bool hasPlayerWon(const Player& player,
                      const GameLib::Game& game) const;

    //--------------------------------------------------------------------------
    // This mehtod determines if there exists a loop for the passed
    // player color. This check is carried out recursively and returns true
    // if a loop exists, otherwise false
    // @param player_color Is is checked if a loop for the player color exists.
    // @param start_tile The tile where the check starts
    // @param previous_tile The tile that is placed before the current tile
    // @param current_tile The tile that is currently checked
    // @param game The current game that takes place
    // @param start_of_recursion This parameter is used to check if the
    //                           recursion just starts
    // @return returns true if a loop exists. Otherwise false
    //
    bool isLoop(Color player_color, TilePtr start_tile, TilePtr previous_tile,
                TilePtr current_tile, const GameLib::Game& game,
                bool start_of_recursion = true) const;

    //--------------------------------------------------------------------------
    // This methode checks if the line of the player color fulfills
    // all winning criteria. If that case occurs, true is returned, oterwise
    // false
    // @param player_color It is checked if the line of the player color
    //                     fullfils all winning criteria
    // @param start_tile The tile where the check begins
    // @param game The current game that takes place
    // @return returns true if the line of the player color fulfills all
    //         winning criteria.
    //
    bool doesLineWin(Color player_color, TilePtr start_tile,
                     const GameLib::Game& game) const;

    //--------------------------------------------------------------------------
    // This method determines if the line of the player color fullfills all
    // winning criteria. If that case occurs, true is returned, otherwise
    // false. This check is carried out recursively
    // @param player_color It is checked if the line of the player color
    //                     fullfils all winning criteria
    // @param previous_tile The tile that is placed before the current tile
    // @param current_tile The tile that is currently checked
    // @param game The current game that takes place
    // @param line_winning_criteria Here are saved all winning criteria
    // @param start_of_recursion This parameter is used to check if the
    //                           recursion just starts.
    // @return returns true if the line of the player color fulfills all
    //         winning criteria.
    //
    void checkIfLineWins(Color player_color, TilePtr previous_tile,
                         TilePtr current_tile, const GameLib::Game& game,
                         LineWinningCriteria& line_winning_criteria,
                         bool start_of_recursion = true) const;

    //--------------------------------------------------------------------------
    // This methode returns a vector of the tiles that are next to the edges of
    // the player color. If one of this tiles is the previous tile it will
    // not be included into the vector
    // @param player_color Only the tiles that are next to the player color
    //                     are returned.
    // @param previous_tile If one of the adjacent tiles is the previous tile it
    //                      will not be included into the vector
    // @param current_tile The tile that is currently checked
    // @param game The current game that takes place
    std::vector<TilePtr> determineNextTiles(Color player_color,
                                            TilePtr previous_tile,
                                            TilePtr current_tile,
                                            const GameLib::Game& game) const;
  public:
    //--------------------------------------------------------------------------
    // method used for retrieving the color of the player which has won
    // @param game reference to instance of game
    // @return returns the color of a player, if a player has won. otherwise
    //         it returns Color::NONE
    //
    Color determineWinner(const GameLib::Game& game) const;

    //--------------------------------------------------------------------------
    // method used for checking if the current situation is a draw
    // @param game reference to instance of game
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
  // @param last_placed std::shared_ptr<Tile> pointing to the tile which was
  //                    last placed
  //
  void doForcedPlay(TilePtr last_placed);

  //----------------------------------------------------------------------------
  // method used for checking if anybody has won
  // @return returns true if a player has won, otherwise returns flase
  //
  bool checkWin();

  //----------------------------------------------------------------------------
  // Method used for checking if it is okay to place a tile
  // @param touching_tiles map containing all tiles which touch the positing of
  //                       the tile
  // @param tile_to_check std::shared_ptr<Tile> pointing to the tile which
  //                      should be checked
  // @return returns true if tile can be placed, otherwise exception is thrown
  //
  bool canTileBePlaced(std::map<TileTypeLib::Edge, TilePtr> touching_tiles,
                       TilePtr tile_to_check);
  //----------------------------------------------------------------------------
  // Method used for checking if the edges of two touching tiles match
  // @param tile_to_check pointer to tile which should be checked
  // @param other pointer to tile which is alredy placed and touches first tile
  // @param touching_edge_of_tile_to_check touching Edge (perspecitve of tile
  //                                       which should be checked)
  // @return returns true if colors match, otherwise returns flase
  //
  bool checkTwoTiles(TilePtr tile_to_check, TilePtr other,
                     TileTypeLib::Edge touching_edge_of_tile_to_check);

public:
  //----------------------------------------------------------------------------
  // Constructor
  //
  GameBoard(const GameLib::Game& game, const std::string& file_name);

  //TODO: delete?
  void startGame();

  //----------------------------------------------------------------------------
  // Method used for trying to add a tile to the gameboard
  // @param position Position on which the tile should be placed
  // @param shape Shape of the tile which should be placed
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
  //         no winner
  //
  std::string getWinner() const;

  //----------------------------------------------------------------------------
  // Method used for writing the gameboard to a file
  // @param file_name Filename (default is no filename)
  //
  void write(const std::string& file_name = "");
};

#endif // GAMEBOARD_H
