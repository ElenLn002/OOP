#include "command_registry.hpp"
#include <stdexcept>

CommandRegistry::CommandRegistry() :
    ValidCommands{ "ADD", "REMOVE", "CHANGE", "DISPLAY" } {} //I guess this is case-sensitive

CommandType CommandRegistry::findCommand(const std::string& commandName) {
    for (const auto& cmd : ValidCommands) {
        if (commandName == cmd) {
            return cmd;
        }
    }

    throw std::runtime_error("Invalid command.");
}
