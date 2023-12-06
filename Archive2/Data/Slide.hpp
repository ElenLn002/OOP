#ifndef SLIDE_HPP
#define SLIDE_HPP

#include "Item.hpp"

#include <vector>

class Slide {
public:
    Slide()=default;

    void addItem(const std::shared_ptr<Item>& item);
    const std::vector<std::shared_ptr<Item>>& getItems() const;

private:
    std::vector<std::shared_ptr<Item>> items;
};

#endif // SLIDE_HPP
