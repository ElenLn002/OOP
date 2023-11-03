#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#include "CommandRegistry.hpp"

class Parser {
public:
    Parser(const std::string& input, CommandRegistry& registry);

    void parse();

private:
    std::string input;
    CommandRegistry& registry;
    std::string command;  
    std::vector<std::string> items;  
    std::string restOfLine; 
    bool validCommand;  
};

#endif //PARSER_HPP
