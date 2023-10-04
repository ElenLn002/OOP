#include "ChangeExecutor.hpp"

ChangeExecutor::ChangeExecutor(int index, const std::string& newArguments)
    : itemIndex(index), newArguments(newArguments) {}

void ChangeExecutor::execute(std::map<int, std::string>& itemsMap) {
    auto it = itemsMap.find(itemIndex);
    if (it != itemsMap.end()) {
        it->second = newArguments;
        std::cout << "Item with index " << itemIndex << " changed." << std::endl;
    }
    else {
        std::cerr << "Item with index " << itemIndex << " not found. No item changed." << std::endl;
    }
}
