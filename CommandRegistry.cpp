#include "CommandRegistry.hpp"

#include<string>

CommandRegistry::CommandRegistry() :
    ValidCommands{ "Add", "Remove", "Quit", "Display", "Save", "Load", "Change" } {}

bool CommandRegistry::isValidCommand(const std::string& commandName) {
    for (const auto& cmd : ValidCommands) {
        if (commandName == cmd) {
            return true;
        }
    }
    return false;
}
