#ifndef COMMANDREGISTRY_HPP
#define COMMANDREGISTRY_HPP

#include <string>
#include <vector>

class CommandRegistry {
public:
    CommandRegistry();
    bool isValidCommand(const std::string& cmd);

private:
    std::vector<std::string> validCommands;
};

#endif// COMMANDREGISTRY_HPP
