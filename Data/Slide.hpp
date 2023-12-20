#ifndef SLIDE_HPP
#define SLIDE_HPP

#include "Item.hpp"

#include <vector>

class Slide {
public:
    void addItem(const std::shared_ptr<Item>& item);
    void removeItem(int itemID);
    std::shared_ptr<Item> getItem(int itemID) const;
    std::map<int, std::shared_ptr<Item>> itemsMap;
};

#endif // SLIDE_HPP
