#include "Item.hpp"

int Item::getID() const {
    return ID;
}

Item::Item(int ID, const shapeType& shape, const std::string& pos, const std::string& attributes) :
    ID(ID), shape(shape), pos(pos), attributes(attributes) {}

shapeType Item::getShape() const {
    return shape;
}

std::string Item::getPosition() const { //I just do not like the name geometry
    return pos;
}

std::string Item::getAttributes() const {
    return attributes;
}

void Item::setAttributes(const std::string& attributes) {
    this->attributes = attributes;
}

void Item::setPosition(const std::string& pos) {
    this->pos = pos;
}
