#include "Controller.hpp"

void Controller::handleAdd(Parser parser) {
    std::vector<std::string> arguments = parser.getArguments();
    if (arguments.size() >= 2) {
        std::string shape = arguments[0];
        std::unordered_set<std::string> attributes(arguments.begin() + 1, arguments.end());

        if (shapeRegistry.isValidShape(shape) && commandValidator.validateShapeAttributes(shape, attributes)) {
            AddExecutor addExecutor(parser.getRestOfTheLine());
            addExecutor.execute(addedItemsMap);
        }
    }
    else {
        std::cerr << "Invalid arguments for Add command." << std::endl;
    }
}


void Controller::handleDisplay(Parser parser) {
    DisplayExecutor displayExecutor(addedItemsMap);
    displayExecutor.execute();
}

void Controller::handleRemove(Parser parser) {
    if (parser.getArguments().size() == 1) {
        int indexToRemove;
        try {
            indexToRemove = std::stoi(parser.getArguments()[0]);
            RemoveExecutor removeExecutor(indexToRemove);
            removeExecutor.execute(addedItemsMap);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid index for Remove command." << std::endl;
        }
    }
    else {
        std::cerr << "Invalid arguments for Remove command." << std::endl;
    }
}

void Controller::handleSave(Parser parser) {
    std::string filePath = parser.getRestOfTheLine();
    filePath = filePath.substr(filePath.find_first_not_of(" "), filePath.find_last_not_of(" ") + 1);

    SaveExecutor saveExecutor(filePath, addedItemsMap);
    saveExecutor.execute();
}

void Controller::handleQuit(Parser parser) {
    QuitExecutor quitExecutor;
    quitExecutor.execute();
}

void Controller::handleChange(Parser parser) {
    if (parser.getArguments().size() >= 2) {
        int indexToChange;
        try {
            indexToChange = std::stoi(parser.getArguments()[0]);
            std::string newArguments = parser.getRestOfTheLine();
            ChangeExecutor changeExecutor(indexToChange, newArguments);
            changeExecutor.execute(addedItemsMap);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid index for Change command." << std::endl;
        }
    }
    else {
        std::cerr << "Invalid arguments for Change command." << std::endl;
    }
}

void Controller::run() {
    while (true) {
        std::cout << "Enter a command: ";
        std::getline(std::cin, userInput);

        Parser parser(userInput, registry);
        parser.parse();

        if (parser.isValidCommand()) {
            std::cout << "Valid command: " << parser.getCommand() << std::endl;

            if (parser.getCommand() == "Add") {
                handleAdd(parser);
            }
            else if (parser.getCommand() == "Display") {
                handleDisplay(parser);
            }
            else if (parser.getCommand() == "Quit") {
                handleQuit(parser);
            }
            else if (parser.getCommand() == "Remove") {
                handleRemove(parser);
            }
            else if (parser.getCommand() == "Save") {
                handleSave(parser);
            }
            else if (parser.getCommand() == "Change") {
                handleChange(parser);
            }
            else {
                std::cerr << "Invalid command." << std::endl;
            }
        }
    }
}
