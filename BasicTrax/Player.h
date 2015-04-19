#ifndef PLAYER_H
#define PLAYER_H

namespace PlayerLib
{
  class Player;

  enum class Color
  {
    NONE,
    WHITE,
    RED
  };

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
}

#endif // PLAYER_H
