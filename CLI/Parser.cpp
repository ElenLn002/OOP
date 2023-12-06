#include "Parser.hpp"

Parser::Parser(const std::string& input, CommandRegistry& registry) :
    input(input), registry(registry), validCommand(false) {
    parse();
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
        }

        items.clear();
        restOfLine.clear();
        for (size_t i = 1; i < tokens.size(); ++i) {
            if (i == 1) {
                restOfLine += tokens[i];
            }
            else {
                restOfLine += " " + tokens[i];
            }
            items.push_back(tokens[i]);
        }
    }
}
