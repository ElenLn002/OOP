#include "Slide.hpp"

void Slide::addItem(const std::shared_ptr<Item>& item) {
    itemsMap[item->getID()] = item;
}

void Slide::removeItem(int itemID) {
    auto it = itemsMap.find(itemID);
    if (it != itemsMap.end()) {
        itemsMap.erase(it);
        std::cout << "Item with ID " << itemID << " removed from slide." << std::endl;
    }
    else {
        std::cout << "Item with ID " << itemID << " not found in the slide." << std::endl;
    }
}

std::shared_ptr<Item> Slide::getItem(int itemID) const {
    auto it = itemsMap.find(itemID);
    if (it != itemsMap.end()) {
        return it->second;
    }
    return nullptr;
}
