#include "ResultPrinter.hpp"

void ResultPrinter:: printItem(int itemID, const std::string& itemAttributes) {
    std::cout << "ID: " << itemID << " Attributes: " << itemAttributes << std::endl;
}

void ResultPrinter:: printItems(const std::map<int, std::string>& itemsMap) {
    for (const auto& entry : itemsMap) {
        printItem(entry.first, entry.second);
    }
}
