#include "DisplatExecutor.hpp"

DisplayExecutor::DisplayExecutor(const std::map<int, std::string>& itemsMap) : itemsMap(itemsMap) {}

void DisplayExecutor::execute() {
    std::cout << "Displaying added items:" << std::endl;
    for (const auto& entry : itemsMap) {
        std::cout << entry.first << " " << entry.second << std::endl;
    }
}

