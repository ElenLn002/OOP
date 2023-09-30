#ifndef COMMAND_REGISTRY_HPP
#define COMMAND_REGISTRY_HPP

#include <string>
#include <vector>

using CommandType = std::string;

class CommandRegistry {
public:
    CommandRegistry();
    CommandType findCommand(const std::string& commandName);

private:
    std::vector<CommandType> ValidCommands;
};

#endif // COMMAND_REGISTRY_HPP
