#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>
#include <sstream>

class Tokenizer {
private:
    std::string input;

public:
     std::istream& takeInput(std::istream& stream);
    std::vector<std::string> getTokens();
};

#endif // TOKENIZER_HPP
