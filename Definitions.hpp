#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <any>
#include <string>
#include <map>


using shapeType = std::string;
using actionType = std::string;
using slideItr = std::map<std::string, std::any>;

const int INITIAL_ITEM_ID = 1;
static const size_t SECOND_ELEMENT_INDEX = 1;


struct Coordinate {
    int row;
    int col;
};

#endif // DEFINITIONS_HPP