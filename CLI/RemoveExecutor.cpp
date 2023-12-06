#include "RemoveExecutor.hpp"

void RemoveExecutor::execute(std::map<int, std::string>& itemsMap) {
    auto it = itemsMap.find(itemID);
    if (it != itemsMap.end()) {
        itemsMap.erase(it);

        // Create a new map with adjusted IDs
        std::map<int, std::string> newItemsMap;
        for (const auto& item : itemsMap) {
            if (item.first > itemID) {
                newItemsMap[item.first - 1] = item.second;
            }
            else {
                newItemsMap[item.first] = item.second;
            }
        }

        itemsMap = newItemsMap;
    }
    else {
        std::cerr << "ID not found: " << itemID << std::endl;
    }
}
