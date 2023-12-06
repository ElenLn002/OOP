#include "Slide.hpp

void Slide::addItem(const std::shared_ptr<Item>& item) {
    items.push_back(item);
}

const std::vector<std::shared_ptr<Item>>& Slide::getItems() const {
    return items;
}
