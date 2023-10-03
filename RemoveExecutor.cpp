#include "RemoveExecutor.hpp"

RemoveExecutor::RemoveExecutor(int index) : itemIndex(index) {}

void RemoveExecutor::removeFromMap(std::map<int, std::string>& itemsMap) {
    auto it = itemsMap.find(itemIndex);
    if (it != itemsMap.end()) {
        itemsMap.erase(it);
        std::cout << "Item with index " << itemIndex << " removed." << std::endl;
    }
    else {
        std::cerr << "Item with index " << itemIndex << " not found. No item removed." << std::endl;
    }
}
