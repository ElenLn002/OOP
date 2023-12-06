#ifndef SLIDE_HPP
#define SLIDE_HPP

#include "Item.hpp"

#include <vector>

class Slide {
public:
    void addItem(const std::shared_ptr<Item>& item);
    void removeItem(int itemID);
    const std::vector<std::shared_ptr<Item>> getItem(int) const;

private:
    std::vector<std::shared_ptr<Item>> items;
};

#endif // SLIDE_HPP
