#include "Parser.hpp"

Parser::Parser(const std::string& input, CommandFactory& factory)
    : input(input), factory(factory), validCommand(false) {
    parseInput();
}

void Parser::parseInput() {
    std::istringstream iss(input);
    Tokenizer tokenizer;
    tokenizer.takeTokens(iss);
    std::vector<std::string> tokens = tokenizer.getTokens();

    if (!tokens.empty()) {
        command = tokens[0];
        // Factory does not have isValidCommand, assuming we need to create the command to check validity
        std::unique_ptr<Command> tempCommand = factory.createCommand(command);

        if (tempCommand) {
            validCommand = true;

            attributesMap.clear();
            // Extract attributes if available
            for (size_t i = 1; i < tokens.size(); ++i) {
                attributesMap[i - 1] = tokens[i];
            }
        }
        else {
            validCommand = false;
        }
    }
}

std::unique_ptr<Command> Parser::parse() {
    if (!validCommand) {
        std::cout << "Invalid command." << std::endl;
        return nullptr;
    }

    std::unique_ptr<Command> commandObj = factory.createCommand(command);

    if (!commandObj) {
        std::cout << "Unknown command." << std::endl;
        return nullptr;
    }

    return commandObj;
}
