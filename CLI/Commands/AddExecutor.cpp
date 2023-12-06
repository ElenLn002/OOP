#include "AddExecutor.hpp"

AddExecutor::AddExecutor(std::string restOfLine) {
    std::istringstream iss(restOfLine);
    std::string token;
    while (iss >> token) {
        if (token[0] != '-') {
            addedAttributes += token + " ";
        }
    }
}

void AddExecutor::execute(std::map<int, std::string>& itemsMap) {
    static int ID = 1;
    itemsMap[ID++] = addedAttributes;
}
