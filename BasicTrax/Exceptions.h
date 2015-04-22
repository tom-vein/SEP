#ifndef EXCEPTIONS
#define EXCEPTIONS

#include "Position.h"

class MessageException : public std::exception
{
public:
  MessageException(std::string message) : message_(message) {}
  virtual ~MessageException() {}
  virtual const char* what() const throw() {return message_.c_str();}
  //std::string getMessage() {return message_;}
protected:
  std::string message_;
};

class PositionException : public MessageException
{
public:
  PositionException(std::string message, Position position) :
    MessageException(message), position_(position) {}
  virtual ~PositionException() {}
  //std::string getMessage() {return message_;}
  Position getPosition() {return position_;}

protected:
  Position position_;
};


class InvalidPositionException : public PositionException
{
public:
  InvalidPositionException(std::string message, Position position) :
    PositionException(message, position) {}
  virtual ~InvalidPositionException() {}
};

class OutOfMemoryException : public MessageException
{
public:
  OutOfMemoryException(std::string message) : MessageException(message) {}
  virtual ~OutOfMemoryException() {}
};

class NoTilesLeftException : public MessageException
{
public:
  NoTilesLeftException(std::string message) : MessageException(message) {}
  virtual ~NoTilesLeftException() {}
};

class NotEmptyException : public PositionException
{
public:
  NotEmptyException(std::string message, Position position) :
    PositionException(message, position) {}
  virtual ~NotEmptyException() {}
};

class ColorMismatchException : public PositionException
{
public:
  ColorMismatchException(std::string message, Position position) :
    PositionException(message, position) {}
  virtual ~ColorMismatchException() {}
};

class TooLessFreeEdgesException : public MessageException
{
public:
  TooLessFreeEdgesException(std::string message) : MessageException(message) {}
  virtual ~TooLessFreeEdgesException() {}
};

class TooManyFreeEdgesException : public MessageException
{
public:
  TooManyFreeEdgesException(std::string message) :
    MessageException(message) {}
  virtual ~TooManyFreeEdgesException() {}
};

class NoSuitableLineDirectionException : public MessageException
{
public:
  NoSuitableLineDirectionException(std::string message) :
    MessageException(message) {}
  virtual ~NoSuitableLineDirectionException() {}
};

class BothLineDirectionAlreadySetException : public MessageException
{
public:
  BothLineDirectionAlreadySetException(std::string message) :
    MessageException(message) {}
  virtual ~BothLineDirectionAlreadySetException() {}
};

class InappropriateNumberOfNextTilesException : public MessageException
{
public:
  InappropriateNumberOfNextTilesException(std::string message) :
    MessageException(message) {}
  virtual ~InappropriateNumberOfNextTilesException() {}
};

class FileWriteException : public MessageException
{
public:
  FileWriteException(std::string message) : MessageException(message) {}
  virtual ~FileWriteException() {}
};

class NoFileNameException : public MessageException
{
public:
  NoFileNameException(std::string message) : MessageException(message) {}
  virtual ~NoFileNameException() {}
};

class InappropriateCommandException : public MessageException
{
public:
  InappropriateCommandException(std::string message) :
    MessageException(message) {}
  virtual ~InappropriateCommandException() {}
};

class WrongUsageProgramException : public MessageException
{
public:
  WrongUsageProgramException(std::string message) :
    MessageException(message) {}
  virtual ~WrongUsageProgramException() {}
};

class WrongParameterException : public MessageException
{
public:
  WrongParameterException(std::string message) :
    MessageException(message) {}
  virtual ~WrongParameterException() {}
};


#endif // EXCEPTIONS

