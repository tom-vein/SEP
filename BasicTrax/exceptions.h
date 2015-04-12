#ifndef EXCEPTIONS
#define EXCEPTIONS

class InvalidPositionException : public std::exception
{
public:
  InvalidPositionException(std::string message, Position position) : message_(message), position_(position) {}
  std::string getMessage() {return message_;}
  Position getPosition() {return position_;}

private:
  std::string message_;
  Position position_;
};

class OutOfMemoryException : public std::exception
{
public:
  OutOfMemoryException(std::string message) : message_(message) {}
  std::string getMessage() {return message_;}
private:
  std::string message_;

};

#endif // EXCEPTIONS

