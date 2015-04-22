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

class Player;

bool operator==(const Player& player01, const Player& player02);

class Player
{
private:
  Color color_;
public:
  Player(Color color);
  Color getColor() const;
  friend bool operator==(const Player& player01, const Player& player02);
};

#endif // PLAYER_H
