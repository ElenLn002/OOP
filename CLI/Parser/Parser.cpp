#include "Parser.hpp"

Parser::Parser(const std::string& input, CommandFactory& factory)
    : input(input), factory(factory), validCommand(false) {
    parseInput();
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
