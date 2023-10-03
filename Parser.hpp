#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#include "CommandRegistry.hpp"


class Parser {
public:
    Parser(const std::string& input, CommandRegistry& registry);

    std::string getCommand() const;
    std::vector<std::string> getArguments() const;
    std::string getRestOfTheLine() const;
    bool isValidCommand() const;

    void parse();

private:
    std::string input;
    CommandRegistry& registry;
    std::string command;  // Store the valid command
    std::vector<std::string> arguments;  // Store the arguments
    std::string restOfTheLine;  // Store the rest of the line
    bool validCommand;  // Flag to indicate if the command is valid
};

#endif //PARSER_HPP