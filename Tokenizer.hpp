#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>
#include <sstream>

class Tokenizer {
private:
    std::string input;

public:
    void takeInput(std::istream& stream);
    std::vector<std::string> getTokens();
};

#endif // TOKENIZER_HPP
