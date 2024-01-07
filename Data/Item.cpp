#include "Item.hpp"


int Item::getID() const {
    return ID;
}

Item::Item(int ID, const shapeType& shape, Coordinate& pos, const std::string& attributes) :
    ID(ID), shape(shape), pos(pos), attributes(attributes) {}

void Item::setID(int ID) {
    this->ID = ID;
}

void Item::setAttributes(std::string& attributes) {
    this->attributes = attributes;
}

shapeType Item::getShape() const {
    return shape;
}

Coordinate Item::getGeom() const {
    return pos;
}

std::string Item::getAttributes() const {
    return attributes;
}

void Item::setAttributes(const std::string& attributes) {
    this->attributes = attributes;
}

void Item::setShape(shapeType shape) {
    this->shape = shape;
}

void Item::setGeom(Coordinate& pos) {
    this->pos = pos;
}
