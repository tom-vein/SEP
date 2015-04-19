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
