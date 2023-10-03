#include "InputTaker.hpp"

std::istream& InputTaker::readInput(std::istream& input, std::string& line) {
    std::getline(input, line);
    return input;
}
