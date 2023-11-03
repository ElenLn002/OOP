#include "Tokenizer.hpp"

void Tokenizer::takeTokens(const std::string input) {
    std::string token;
    std::istringstream iss(input);
    while (iss >> token) {
        tokens.push_back(token);
    }
}

std::vector<std::string> Tokenizer::getTokens() const {
    return tokens;
}
