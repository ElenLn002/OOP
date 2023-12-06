#include "Slide.hpp

void Slide::addItem(const std::shared_ptr<Item>& item) {
    items.push_back(item);
}

const std::vector<std::shared_ptr<Item>> Slide::getItem(int slideID) const {
    std::vector<std::shared_ptr<Item>> foundItems;

    for (const auto& item : items) {
        if (item->getID() == slideID) {
            foundItems.push_back(item);
        }
    }

    return foundItems;
}

void Slide::removeItem(int itemID) {
    auto it = std::find_if(items.begin(), items.end(), [itemID](const std::shared_ptr<Item>& item) {
        return item->getID() == itemID;
        });

    if (it != items.end()) {
        items.erase(it);
        std::cout << "Item with ID " << itemID << " removed from slide." << std::endl;
    }
    else {
        std::cout << "Item with ID " << itemID << " not found in the slide." << std::endl;
    }
}
