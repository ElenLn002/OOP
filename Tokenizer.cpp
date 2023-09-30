#include "tokenizer.hpp"

void Tokenizer::takeInput(std::istream& stream) {
    // Read input from the stream
    std::stringstream buffer;
    buffer << stream.rdbuf();
    input = buffer.str();
}

std::vector<std::string> Tokenizer::getTokens() {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    // Tokenize based on whitespace
    while (ss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}
