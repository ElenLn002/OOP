#include "CommandRegistry.hpp"

#include<string>

CommandRegistry::CommandRegistry() :
    validCommands{ "Add", "Remove", "Save", "Display", "List", "Change", "Quit", "Undo", "Redo" } {}

bool CommandRegistry::isValidCommand(const std::string& commandName) {
    for (const auto& input : validCommands) {
        if (commandName == input) {
            return true;
        }
    }
    return false;
}
