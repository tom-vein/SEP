//------------------------------------------------------------------------------
// Player.h
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Color.h"

//------------------------------------------------------------------------------
// Forward declarations
//
class Player;
bool operator==(const Player& first_player, const Player& second_player);

class Player
{
private:
  //----------------------------------------------------------------------------
  // Color of the player
  //
  Color color_;

public:
  //----------------------------------------------------------------------------
  // constructor
  //
  Player(Color color);

  //----------------------------------------------------------------------------
  // Getter
  //
  Color getColor() const;

  //----------------------------------------------------------------------------
  // Implementation of operator ==
  //
  friend bool operator==(const Player& first_player,
                         const Player& second_player);
};

#endif // PLAYER_H
