#include "ActionInterface.hpp"

#include <iostream>
#include <stack>
#include <map>
#include <string>


class Redo : public ActionInterface {
public:
    Redo(std::stack<std::map<int, std::string>>& undoStack, std::stack<std::map<int, std::string>>& redoStack, std::map<int, std::string>& itemsMap);
    void execute() override;

private:
    std::stack<std::map<int, std::string>>& undoStack;
    std::stack<std::map<int, std::string>>& redoStack;
    std::map<int, std::string>& itemsMap;
};