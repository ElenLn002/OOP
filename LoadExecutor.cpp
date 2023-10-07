#include "LoadExecutor.hpp"

LoadExecutor::LoadExecutor(std::map<int, std::string>& itemsMap)
    : itemsMap(itemsMap) {}


void LoadExecutor::execute() {
    for (const auto& it : itemsMap) {
        std::cout << it.first << std::endl;
    }
}