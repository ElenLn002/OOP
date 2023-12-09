#ifndef ITEXTDISPLAYABLE_HPP
#define ITEXTDISPLAYABLE_HPP

#include <memory>
#include <sstream>

class ITextDisplayable {
public:
    virtual void display(std::shared_ptr<Item> item, std::ostream& output) = 0;
};

#endif //ITEXTDISPLAYABLE_HPP
