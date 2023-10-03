#include "Tokenizer.hpp"

void Tokenizer::takeTokens(const std::string& input) {
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
}

std::vector<std::string> Tokenizer::getTokens() {
    return tokens;
}