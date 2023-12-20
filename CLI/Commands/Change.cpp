#include "Change.hpp"

Change::Change(int ID, std::string& newAttributes) :
    itemID(ID), newAttributes(newAttributes) {}

void Change::execute(std::map<int, std::string>& itemsMap) {
    auto it = itemsMap.find(itemID);
    if (it != itemsMap.end()) {
        it->second = newAttributes;
    }
    else {
        std::cerr << "ID not found" << std::endl;
    }
}
