//------------------------------------------------------------------------------
// Exceptions.h
//
// Group: Group 11599, study assistant Philipp Hafner
//
// Authors:
// Thomas Hoedl 1430320
// Mario Theuermann 1430751
// Stephan Valentan 1430529
//------------------------------------------------------------------------------
//

#ifndef EXCEPTIONS
#define EXCEPTIONS

#include "Position.h"

//----------------------------------------------------------------------------
// Base class for all exceptions
// provides functionality to create exception with a message
//
class MessageException : public std::exception
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  MessageException(std::string message) : message_(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~MessageException() {}

  //--------------------------------------------------------------------------
  // overridden what Method
  // usally called if reason of exception should be displayed
  // @return Returns message of exception
  //
  virtual const char* what() const throw() {return message_.c_str();}

protected:
  //--------------------------------------------------------------------------
  // Error message
  //
  std::string message_;
};

//----------------------------------------------------------------------------
// class providion additional position for a exception
// used if position of error is needed
//
class PositionException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  PositionException(std::string message, Position position) :
    MessageException(message), position_(position) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~PositionException() {}

  //--------------------------------------------------------------------------
  // Getter-Method to retrieve position of tile which caused exception
  // @return Returns position of tile which caused exception
  //
  Position getPosition() {return position_;}

protected:
  //--------------------------------------------------------------------------
  // Position of tile which caused the exception
  //
  Position position_;
};

//----------------------------------------------------------------------------
// Exception if a position is invalid
//
class InvalidPositionException : public PositionException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  InvalidPositionException(std::string message, Position position) :
    PositionException(message, position) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~InvalidPositionException() {}
};

//----------------------------------------------------------------------------
// Exception there is no memory left
//
class OutOfMemoryException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  OutOfMemoryException(std::string message) : MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~OutOfMemoryException() {}
};

//----------------------------------------------------------------------------
// Exception if there are no tiles left
//
class NoTilesLeftException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  NoTilesLeftException(std::string message) : MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~NoTilesLeftException() {}
};

//----------------------------------------------------------------------------
// Exception if the position is not empty
//
class NotEmptyException : public PositionException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  NotEmptyException(std::string message, Position position) :
    PositionException(message, position) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~NotEmptyException() {}
};

//----------------------------------------------------------------------------
// Exception if a tile cannot be placed because the touching colors
// do not match with tile which should be placed
//
class ColorMismatchException : public PositionException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  ColorMismatchException(std::string message, Position position) :
    PositionException(message, position) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~ColorMismatchException() {}
};

//TODO: add header
class TooLessFreeEdgesException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  TooLessFreeEdgesException(std::string message) : MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~TooLessFreeEdgesException() {}
};

//TODO: add header
class TooManyFreeEdgesException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  TooManyFreeEdgesException(std::string message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~TooManyFreeEdgesException() {}
};

//TODO: add header
class NoSuitableLineDirectionException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  NoSuitableLineDirectionException(std::string message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~NoSuitableLineDirectionException() {}
};

//TODO: add header
class BothLineDirectionAlreadySetException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  BothLineDirectionAlreadySetException(std::string message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~BothLineDirectionAlreadySetException() {}
};

//TODO: add header
class InappropriateNumberOfNextTilesException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  InappropriateNumberOfNextTilesException(std::string message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~InappropriateNumberOfNextTilesException() {}
};

//TODO: add header
class FileWriteException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  FileWriteException(std::string message) : MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~FileWriteException() {}
};

//TODO: add header
class NoFileNameException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  NoFileNameException(std::string message) : MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~NoFileNameException() {}
};

//TODO: add header
class InappropriateCommandException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  InappropriateCommandException(std::string message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~InappropriateCommandException() {}
};

//TODO: add header
class WrongUsageProgramException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  WrongUsageProgramException(std::string message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~WrongUsageProgramException() {}
};

//TODO: add header
class WrongParameterException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  WrongParameterException(std::string message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~WrongParameterException() {}
};


#endif // EXCEPTIONS

