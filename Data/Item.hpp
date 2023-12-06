#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

using shapeType = std::string;

class Item {
public:
    Item(int ID, const shapeType& shape, const std::string& pos, const std::string& attributes);

    shapeType getShape() const;
    std::string getPosition() const;
    std::string getAttributes() const;
    int getID() const;

    void setAttributes(const std::string& attributes);
    void setPosition(const std::string& pos);

private:
    std::string attributes;
    shapeType shape;
    std::string pos;
    int ID;
};

#endif //ITEM_HPP
