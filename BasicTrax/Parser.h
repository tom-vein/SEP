#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

class Command;

class Parser
{
public:
  Parser();
  const Command& parseCommand(const std::string& command_string) const;
  static const std::string& parseArguments(int argc, char* argv[]) const;
};

#endif // PARSER_H
