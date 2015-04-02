#ifndef PLAYER_H
#define PLAYER_H

#include "Color.h"

class Player
{
private:
  Color color_;
public:
  Player(Color color);
  void placeTile();
};

#endif // PLAYER_H
