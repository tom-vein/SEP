#ifndef PLAYER_H
#define PLAYER_H

namespace PlayerLib
{
  enum class Color
  {
    NONE,
    WHITE,
    RED
  };

  class Player
  {
  private:
    Color color_;
  public:
    Player(Color color);
    void placeTile();
  };
}

#endif // PLAYER_H
