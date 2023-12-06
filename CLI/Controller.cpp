#include "Controller.hpp"

void Controller::run() {
    CommandRegistry cmdreg;
    bool flag = true;
    while (flag) {
        std::cout << "Enter a command: ";
        std::string userInput;
        std::getline(std::cin, userInput);

        std::istringstream iss(userInput);
        std::string command;
        iss >> command;
        command = trim(command);

        if (cmdreg.isValidCommand(command)) {
            std::string restOfTheLine = trim(userInput.substr(command.length()));

            if (command == "Add") {
                undoStack.push(itemsMap);
                handleAdd(restOfTheLine);
            }
            else if (command == "Display") {
                handleDisplay(restOfTheLine);
            }
            else if (command == "Quit") {
                flag = false;
            }
            else if (command == "Remove") {
                undoStack.push(itemsMap);
                handleRemove(restOfTheLine);
            }
            else if (command == "Save") {
                handleSave(restOfTheLine);
            }
            else if (command == "Load") {
                handleLoad(restOfTheLine);
            }
            else if (command == "Change") {
                undoStack.push(itemsMap);
                handleChange(restOfTheLine);
            }
            else if (command == "List") {
                handleList();
            }
            else if (command == "Undo") {
                handleUndo();
            }
            else if (command == "Redo") {
                handleRedo();
            }
        }
        else {
            std::cerr << "Invalid command." << std::endl;
        }
    
    }
}

void Controller::handleUndo() {
    Undo undo(undoStack, redoStack, itemsMap);
    undo.execute();
}

void Controller::handleRedo() {
    Redo redo(undoStack, redoStack, itemsMap);
    redo.execute();
}

void Controller::handleAdd(const std::string& restOfTheLine) {
    AddExecutor addExecutor(restOfTheLine);
    addExecutor.execute(itemsMap);
}

void Controller::handleDisplay(const std::string& restOfTheLine) {
    std::istringstream argStream(restOfTheLine);
    int displayID;
    argStream >> displayID;

    if (argStream) {
        DisplayExecutor displayExecutor(displayID, itemsMap);
        displayExecutor.execute(itemsMap);
    }
    else {
        std::cerr << "Error: Invalid ID for Display command." << std::endl;
    }
}

void Controller::handleLoad(const std::string& restOfTheLine) {
    if (!restOfTheLine.empty()) {
        std::string filePath = trim(restOfTheLine);
        LoadExecutor loadExecutor(filePath, &INITIAL_ITEM_ID); // Pass the pointer
        loadExecutor.execute(itemsMap);
    }
    else {
        std::cerr << "Invalid arguments for Load command." << std::endl;
    }
}


void Controller::handleRemove(const std::string& restOfTheLine) {
    if (!restOfTheLine.empty()) {
        int itemID;
        try {
            itemID = std::stoi(restOfTheLine);
            RemoveExecutor removeExecutor(itemID);
            removeExecutor.execute(itemsMap);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid ID for Remove command." << std::endl;
        }
    }
    else {
        std::cerr << "Error: Invalid arguments for Remove command." << std::endl;
    }
}


void Controller::handleSave(const std::string& restOfTheLine) {
    if (!restOfTheLine.empty()) {
        std::string filePath = trim(restOfTheLine);
        SaveExecutor saveExecutor(filePath, itemsMap);
        saveExecutor.execute(itemsMap);
    }
    else {
        std::cerr << "Invalid arguments for Save command." << std::endl;
    }
}

void Controller::handleChange(const std::string& restOfTheLine) {
    std::istringstream argStream(restOfTheLine);
    int indexToChange;
    argStream >> indexToChange;
    std::string newArguments = trim(restOfTheLine.substr(restOfTheLine.find_first_of(" ") + 1));

    if (argStream && !newArguments.empty()) {
        ChangeExecutor changeExecutor(indexToChange, newArguments);
        changeExecutor.execute(itemsMap);
    }
    else {
        std::cerr << "Invalid arguments for Change command." << std::endl;
    }
}

void Controller::handleList() {
    ListExecutor listExecutor(itemsMap);
    listExecutor.execute(itemsMap);
}
