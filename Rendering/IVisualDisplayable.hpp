#ifndef IVISUALDISPLAYABLE_HPP
#define IVISUALDISPLAYABLE_HPP

#include <memory>
#include <QPainter>
#include "Item.hpp"


class IVisualDisplayable {
public:
    virtual void draw(QPainter* painter, std::shared_ptr<Item> item) = 0;
};

#endif //IVISUALDISPLAYABLE_HPP
