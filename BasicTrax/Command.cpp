//------------------------------------------------------------------------------
// Filename: Command.cpp
// Description: Class representing a general command
// Authors: Tutors
// Tutor: Tutors
// Group: 42
// Created: 02.09.2011
// Last change: 02.09.2011
//------------------------------------------------------------------------------

#include "Command.h"


//------------------------------------------------------------------------------
CommandLib::Command::Command(std::string name) : command_name_(name)
{
}

//------------------------------------------------------------------------------
virtual CommandLib::Command::~Command()
{
}

//------------------------------------------------------------------------------
const std::string& CommandLib::SCommand::getName() const
{
  return command_name_;
}
