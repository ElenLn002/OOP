#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using shapeType = std::string;

struct Coordinate {
    int x;
    int y;
};

class Item {
public:
    Item(int ID, const shapeType& shape, Coordinate& pos, const std::string& attributes);

    void setShape(shapeType shape);
    shapeType getShape() const;

    void setGeom(Coordinate& coord);
    Coordinate getGeom() const;

    void setAttributes(std::string& attributes);
    std::string getAttributes() const;

    void setID(int ID);
    int getID() const;

    void setAttributes(const std::string& attributes);

private:
    std::string attributes;
    shapeType shape;
    Coordinate pos;
    int ID;
};
#endif //ITEM_HPP
