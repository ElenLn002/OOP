#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#include "ConcreteCommandFactory.hpp"

class Parser {
public:
    Parser(const std::string& input, CommandFactory& factory);

    std::unique_ptr<Command> parse();

private:
    std::string input;
    CommandFactory& factory;

    std::string command;
    std::unordered_map<int, std::string> attributesMap;
    bool validCommand;

    void parseInput();
};
#endif //PARSER_HPP
