#ifndef POSITION_H
#define POSITION_H

#include <string>
#include <sstream>

class Position
{
private:
  int x_;
  int y_;
public:
  Position(int x, int y);

  int getX() const;
  int getY() const;

  bool parse(const std::string& input);

  const std::string toString() const;
};

#endif // POSITION_H
