#include "Redo.hpp"

Redo::Redo(std::stack<std::map<int, std::string>>& undoStack, std::stack<std::map<int, std::string>>& redoStack, std::map<int, std::string>& itemsMap)
    : undoStack(undoStack), redoStack(redoStack), itemsMap(itemsMap) {}

void Redo::execute() {
    if (!redoStack.empty()) {
        undoStack.push(itemsMap);
        itemsMap = redoStack.top();
        redoStack.pop();
        std::cerr << "Redo operation performed." << std::endl;
    }
    else {
        std::cerr << "No actions to redo." << std::endl;
    }
}