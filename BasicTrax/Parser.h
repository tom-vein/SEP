#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

class Command;

class Parser
{
public:
  Parser();
  //Here all checks are done and for the further steps it will be determined
  //that the command is and its parameters are valid and do not needed to be
  //checked again
  const Command& parseCommand(const std::string& command_string) const;
  static const std::string& parseArguments(int argc, char* argv[]) const;
};

#endif // PARSER_H
