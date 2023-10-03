#include "Controller.hpp"

void Controller::run() {
    CommandRegistry registry;
    std::string userInput;
    std::map<int, std::string> addedItemsMap;

    ShapeRegistry shapeRegistry;
    CommandValidator commandValidator;

    while (true) {
        std::cout << "Enter a command: ";
        std::getline(std::cin, userInput);

        Parser parser(userInput, registry);
        parser.parse();

        if (parser.isValidCommand()) {
            std::cout << "Valid command: " << parser.getCommand() << std::endl;

            if (parser.getCommand() == "Add") {
                std::vector<std::string> arguments = parser.getArguments();
                if (arguments.size() >= 2) {
                    std::string shape = arguments[0];
                    std::unordered_set<std::string> attributes(arguments.begin() + 1, arguments.end());

                    if (shapeRegistry.isValidShape(shape) && commandValidator.validateShapeAttributes(shape, attributes)) {
                        AddExecutor addExecutor(parser.getRestOfTheLine());
                        addExecutor.addToMap(addedItemsMap);
                        std::cout << "Items added." << std::endl;
                    }
                }
                else {
                    std::cerr << "Invalid arguments for Add command." << std::endl;
                }
            }
            // Add other command cases here

            else if (parser.getCommand() == "Display") {
                DisplayExecutor displayExecutor(addedItemsMap);
                displayExecutor.execute();
            }
            else if (parser.getCommand() == "Quit") {
                QuitExecutor quitExecutor;
                quitExecutor.execute();
            }
            else if (parser.getCommand() == "Remove") {
                if (parser.getArguments().size() == 1) {
                    int indexToRemove;
                    try {
                        indexToRemove = std::stoi(parser.getArguments()[0]);
                        RemoveExecutor removeExecutor(indexToRemove);
                        removeExecutor.removeFromMap(addedItemsMap);
                    }
                    catch (const std::invalid_argument& e) {
                        std::cerr << "Invalid index for Remove command." << std::endl;
                    }
                }
                else {
                    std::cerr << "Invalid arguments for Remove command." << std::endl;
                }
            }
            else if (parser.getCommand() == "Save") {
                std::string filePath = parser.getRestOfTheLine();
                filePath = filePath.substr(filePath.find_first_not_of(" "), filePath.find_last_not_of(" ") + 1);

                SaveExecutor saveExecutor(filePath, addedItemsMap);
                saveExecutor.execute();
            }
        }
        else {
            std::cerr << "Invalid command." << std::endl;
        }
    }
}
