#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <any>
#include <memory>
#include <iterator>
#include <unordered_map>
#include <fstream>
#include <sstream>


#include "CommandRegistry.hpp"
#include "CommandValidator.hpp"
#include "ShapeRegistry.hpp"
#include "Parser.hpp"
#include "Utils.hpp"

class Controller {
public:
    void run();

private:
    std::map<int, std::string> itemsMap;
    std::stack<std::map<int, std::string>> undoStack;
    std::stack<std::map<int, std::string>> redoStack;

    void handleAdd(const std::string& restOfTheLine);
    void handleDisplay(const std::string& restOfTheLine);
    void handleRemove(const std::string& restOfTheLine);
    void handleSave(const std::string& restOfTheLine);
    void handleLoad(const std::string& restOfTheLine);
    void handleChange(const std::string& restOfTheLine);
    void handleList();
    void handleUndo();
    void handleRedo();
};
