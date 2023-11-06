#include "Undo.hpp"

Undo::Undo(std::stack<std::map<int, std::string>>& undoStack, std::stack<std::map<int, std::string>>& redoStack, std::map<int, std::string>& itemsMap)
    : undoStack(undoStack), redoStack(redoStack), itemsMap(itemsMap) {}

void Undo::execute() {
    if (!undoStack.empty()) {
        redoStack.push(itemsMap);
        itemsMap = undoStack.top();
        undoStack.pop();
        std::cerr << "Undo operation performed." << std::endl;
    }
    else {
        std::cerr << "No actions to undo." << std::endl;
    }
}