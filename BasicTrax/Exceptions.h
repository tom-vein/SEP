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
  MessageException(const char* message) : message_(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~MessageException() {}

  //--------------------------------------------------------------------------
  // overridden what Method
  // usally called if reason of exception should be displayed
  // @return Returns message of exception
  //
  virtual const char* what() const noexcept {return message_;}

protected:
  //--------------------------------------------------------------------------
  // Error message
  //
  const char* message_;
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
  PositionException(const char* message, Position position) :
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
  InvalidPositionException(const char* message, Position position) :
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
  OutOfMemoryException(const char* message) : MessageException(message) {}

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
  NoTilesLeftException(const char* message) : MessageException(message) {}

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
  NotEmptyException(const char* message, Position position) :
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
  ColorMismatchException(const char* message, Position position) :
    PositionException(message, position) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~ColorMismatchException() {}
};

//----------------------------------------------------------------------------
// This exception is used to determine if there are too less free edges
// around a tile
//
class TooLessFreeEdgesException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  TooLessFreeEdgesException(const char* message) : MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~TooLessFreeEdgesException() {}
};

//----------------------------------------------------------------------------
// This exception is used to determine if there are too many free edges
// around a tile
//
class TooManyFreeEdgesException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  TooManyFreeEdgesException(const char* message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~TooManyFreeEdgesException() {}
};

//----------------------------------------------------------------------------
// This exception says that there are no suitable line directions
//
class NoSuitableLineDirectionException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  NoSuitableLineDirectionException(const char* message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~NoSuitableLineDirectionException() {}
};

//----------------------------------------------------------------------------
// This exception is used to inform if both line direction are already set
//
class BothLineDirectionAlreadySetException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  BothLineDirectionAlreadySetException(const char* message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~BothLineDirectionAlreadySetException() {}
};

//----------------------------------------------------------------------------
// This exception is used to inform if the number of tiles in for example
// vector is inappropriate
//
class InappropriateNumberOfNextTilesException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  InappropriateNumberOfNextTilesException(const char* message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~InappropriateNumberOfNextTilesException() {}
};

//----------------------------------------------------------------------------
// This excetpion is used to inform that an error occured during writing to
// file
//
class FileWriteException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  FileWriteException(const char* message) : MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~FileWriteException() {}
};

//----------------------------------------------------------------------------
// This exception informs that no file name has specified and so no writing
// to file can be carried out
//
class NoFileNameException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  NoFileNameException(const char* message) : MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~NoFileNameException() {}
};

//----------------------------------------------------------------------------
// This exception informs that the usage of the program is wrong because
// for example the user entered wrong parameters when he started the program
//
class WrongUsageProgramException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  WrongUsageProgramException(const char* message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~WrongUsageProgramException() {}
};

//----------------------------------------------------------------------------
// This exception informs that the parameters to a command are wrong
//
class WrongParameterException : public MessageException
{
public:
  //--------------------------------------------------------------------------
  // Constructor
  //
  WrongParameterException(const char* message) :
    MessageException(message) {}

  //--------------------------------------------------------------------------
  // Destructor
  //
  virtual ~WrongParameterException() {}
};

#endif // EXCEPTIONS

