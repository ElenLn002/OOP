#include "Parser.hpp"
#include "CLIController.hpp"
#include "Includes.hpp"

std::unique_ptr<Command> CLIController::parseCommand(const std::string& input) {
    Parser parser(input, registry_);
    return parser.parse();
}

void CLIController::executeCommands(std::istream& inputStream) {
    std::string input;
    while (std::getline(inputStream, input)) {
        input = trim(input);

        std::unique_ptr<Command> command = parseCommand(input);
        if (command) {
            command->execute();

            history_.addToHistory(input);
        }
    }
}

