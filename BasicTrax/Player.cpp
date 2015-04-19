#include "Player.h"

PlayerLib::Player::Player(Color color) : color_(color)
{

}

PlayerLib::Color PlayerLib::Player::getColor() const
{
  return color_;
}

bool PlayerLib::operator==(const Player& player01, const Player& player02)
{
  if(player01.color_ == player02.color_)
    return true;

  return false;
}
