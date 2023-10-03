#ifndef SHAPEREGISTRY_HPP
#define SHAPEREGISTRY_HPP

#include <string>
#include <vector>

class ShapeRegistry {
public:
    ShapeRegistry();
    bool isValidShape(const std::string& shapeName);

private:
    std::vector<CommandType> ValidShapes;
};



#endif //SHAPEREGISTRY_HPP