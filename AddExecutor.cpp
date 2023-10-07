#include "AddExecutor.hpp"

AddExecutor::AddExecutor(const std::string& restOfTheLine) {
    std::istringstream iss(restOfTheLine);
    std::string token;
    while (iss >> token) {
        if (token[0] != '-')
            addedItems += token + " ";
    }
}

void AddExecutor::execute(std::map<int, std::string>& itemsMap) {
    static int index = 1;
    itemsMap[index++] = addedItems;
}
