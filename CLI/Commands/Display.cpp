#include "Display.hpp"

DisplayExecutor::Display(int ID, const std::map<int, std::string>& itemsMap)
    : itemID(ID), itemsMap(itemsMap) {}

void Display::execute(std::map<int, std::string>& itemsMap) {
        auto it = itemsMap.find(itemID);
        if (it != itemsMap.end()) {
            resultPrinter.printItem(itemID, it->second);
        }
        else {
            std::cerr << "ID not found: " << itemID << std::endl;
        }
    
}

