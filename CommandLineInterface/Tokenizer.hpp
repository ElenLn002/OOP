#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

class Tokenizer {
public:
    void takeTokens(const std::string input);
    std::vector<std::string> getTokens() const;

private:
    std::string token;
    std::vector<std::string> tokens;
};


#endif //TOKENIER_HPP
