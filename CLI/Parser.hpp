#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#include "CommandRegistry.hpp"

class Parser {
public:
    Parser(const std::string& input, CommandRegistry& registry);

    std::unique_ptr<Command> parse();


private:
    std::string input;
    CommandRegistry& registry;

    std::string command;
    std::unordered_map<int, std::string> attributesMap;
    bool validCommand;

    void parseInput();
};

#endif //PARSER_HPP
