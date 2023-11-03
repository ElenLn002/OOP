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
                handleAdd(restOfTheLine);
            }
            else if (command == "Display") {
                handleDisplay();
            }
            else if (command == "Quit") {
                flag = false;
            }
            else if (command == "Remove") {
                handleRemove(restOfTheLine);
            }
            else if (command == "Save") {
                handleSave(restOfTheLine);
            }
            else if (command == "Change") {
                handleChange(restOfTheLine);
            }
            else if (command == "List") {
                handleList();
            }
        }
        else {
            std::cerr << "Invalid command." << std::endl;
        }
    }
}

void Controller::handleAdd(const std::string& restOfTheLine) {
    AddExecutor addExecutor(restOfTheLine);
    addExecutor.execute(itemsMap);
}

void Controller::handleDisplay() {
    int displayID;
    std::cout << "Enter the ID to display: ";
    std::cin >> displayID;

    auto it = itemsMap.find(displayID);
    if (it != itemsMap.end()) {
        DisplayExecutor displayExecutor(displayID, itemsMap);
        displayExecutor.execute(itemsMap);
    }
    else {
        std::cerr << "ID not found: " << displayID << std::endl;
    }
}

void Controller::handleRemove(const std::string& restOfTheLine) {
    if (!restOfTheLine.empty()) {
        int indexToRemove;
        try {
            indexToRemove = std::stoi(restOfTheLine);
            RemoveExecutor removeExecutor(indexToRemove);
            removeExecutor.execute(itemsMap);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid index for Remove command." << std::endl;
        }
    }
    else {
        std::cerr << "Invalid arguments for Remove command." << std::endl;
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
