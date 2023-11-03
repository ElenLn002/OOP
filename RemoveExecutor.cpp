#include "RemoveExecutor.hpp"

RemoveExecutor::RemoveExecutor(int ID) : itemID(ID) {}

void RemoveExecutor::execute(std::map<int, std::string>& itemsMap) {
    auto it = itemsMap.find(itemID);
    if (it != itemsMap.end()) {
        itemsMap.erase(it);
    }
    else {
        std::cerr << "ID not found" << std::endl;
    }
}
