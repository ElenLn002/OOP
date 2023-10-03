#include "Parser.hpp"

Parser::Parser(const std::string& input, CommandRegistry& registry) :
    input(input), registry(registry), validCommand(false) {}

std::string Parser::getCommand() const {
    return command;
}

std::vector<std::string> Parser::getArguments() const {
    return arguments;
}

std::string Parser::getRestOfTheLine() const {
    return restOfTheLine;
}

bool Parser::isValidCommand() const {
    return validCommand;
}

void Parser::parse() {
    Tokenizer tokenizer;
    tokenizer.takeTokens(input);
    std::vector<std::string> tokens = tokenizer.getTokens();

    if (!tokens.empty()) {
        std::string possibleCommand = tokens[0];
        if (registry.isValidCommand(possibleCommand)) {
            validCommand = true;
            command = possibleCommand;

            // Store the arguments and the rest of the line
            arguments.clear();
            restOfTheLine.clear();
            for (size_t i = 1; i < tokens.size(); ++i) {
                if (i == 1) {
                    restOfTheLine += tokens[i];
                }
                else {
                    restOfTheLine += " " + tokens[i];
                }
                arguments.push_back(tokens[i]);
            }
        }
        else {
            std::cerr << "Invalid command." << std::endl;
        }
    }
}