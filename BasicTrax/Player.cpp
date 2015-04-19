#include "Player.h"

Player::Player(Color color) : color_(color)
{

}

Color Player::getColor() const
{
  return color_;
}

bool operator==(const Player& player01, const Player& player02)
{
  if(player01.color_ == player02.color_)
    return true;

  return false;
}
