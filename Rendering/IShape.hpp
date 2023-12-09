#ifndef ISHAPE_HPP
#define ISHAPE_HPP

#include "Item.hpp"
#include <memory>
#include <sstream>

class ITextDisplayable {
public:
    virtual void display(std::shared_ptr<Item> item, std::ostream& output) = 0;
};

#endif //ISHAPE_HPP
