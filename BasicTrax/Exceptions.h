#ifndef EXCEPTIONS
#define EXCEPTIONS

class MessageException : public std::exception
{
public:
  MessageException(std::string message) : message_(message) {}
  virtual ~MessageException() {}
  std::string getMessage() {return message_;}
protected:
  std::string message_;
};

class PositionException : public MessageException
{
public:
  PositionException(std::string message, Position position) : MessageException(message), position_(position) {}
  virtual ~PositionException() {}
  std::string getMessage() {return message_;}
  Position getPosition() {return position_;}

protected:
  Position position_;
};


class InvalidPositionException : public PositionException
{
public:
  InvalidPositionException(std::string message, Position position) : PositionException(message, position) {}
  ~InvalidPositionException() {}
};

class OutOfMemoryException : public MessageException
{
public:
  OutOfMemoryException(std::string message) : MessageException(message) {}
  ~OutOfMemoryException() {}
};
class NoTilesLeftException : public MessageException
{
public:
  NoTilesLeftException(std::string message) : MessageException(message) {}
  ~NoTilesLeftException() {}
};
class NotEmptyException : public PositionException
{
public:
  NotEmptyException(std::string message, Position position) : PositionException(message, position) {}
  ~NotEmptyException() {}
};
class ColorMismatchException : public PositionException
{
public:
  ColorMismatchException(std::string message, Position position) : PositionException(message, position) {}
  ~ColorMismatchException() {}
};


#endif // EXCEPTIONS

