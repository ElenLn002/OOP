#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <unordered_set>
#include <map>

#include "CommandRegistry.hpp"
#include "CommandValidator.hpp"
#include "ShapeRegistry.hpp"
#include "Parser.hpp"



class Controller {
public:
    void run();

public:
    void handleAdd(Parser);
    void handleDisplay(Parser);
    void handleRemove(Parser);
    void handleSave(Parser);
    void handleQuit(Parser);
    void handleChange(Parser);

private:
    CommandRegistry registry;
    std::string userInput;
    std::map<int, std::string> addedItemsMap;

    ShapeRegistry shapeRegistry;
    CommandValidator commandValidator;
};

#endif //CONTROLLER_HPP
