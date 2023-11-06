#include "ChangeExecutor.hpp"

ChangeExecutor::ChangeExecutor(int ID, std::string& newAttributes) :
    itemID(ID), newAttributes(newAttributes) {}

void ChangeExecutor::execute(std::map<int, std::string>& itemsMap) {
    auto it = itemsMap.find(itemID);
    if (it != itemsMap.end()) {
        it->second = newAttributes;
    }
    else {
        std::cerr << "ID not found" << std::endl;
    }
}
