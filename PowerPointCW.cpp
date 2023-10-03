#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <stdexcept>
#include <unordered_set>
#include <map>

using CommandType = std::string;
using ShapeType = std::string;

class CommandRegistry {
public:
    CommandRegistry();
    bool isValidCommand(const std::string& commandName);

private:
    std::vector<CommandType> ValidCommands;
};

CommandRegistry::CommandRegistry() :
    ValidCommands{ "Add", "Remove", "Quit", "Display", "Save", "Load" } {}

bool CommandRegistry::isValidCommand(const std::string& commandName) {
    for (const auto& cmd : ValidCommands) {
        if (commandName == cmd) {
            return true;
        }
    }
    return false;
}



class CommandValidator {
public:
    CommandValidator();
    bool validateShapeAttributes(const std::string& shape, const std::unordered_set<std::string>& attributes);

private:
    std::unordered_set<std::string> circleAttributes;
    std::unordered_set<std::string> rectangleAttributes;
    std::unordered_set<std::string> triangleAttributes;
};

CommandValidator::CommandValidator() {
    circleAttributes = { "-colour", "-style", "-pos", "-rad" };
    rectangleAttributes = { "-colour", "-style", "-TL", "-RB" };
    triangleAttributes = { "-colour", "-style", "-pos" };
}

bool CommandValidator::validateShapeAttributes(const std::string& shape, const std::unordered_set<std::string>& attributes) {
    std::unordered_set<std::string> allowedAttributes;

    if (shape == "circle") {
        allowedAttributes = circleAttributes;
    }
    else if (shape == "rectangle") {
        allowedAttributes = rectangleAttributes;
    }
    else if (shape == "triangle") {
        allowedAttributes = triangleAttributes;
    }
    else {
        std::cout << "Validation for shape " << shape << " not implemented." << std::endl;
        return false;
    }

    for (const auto& attr : attributes) {
        // Check if the attribute starts with a dash ("-") and if it's in the allowed attributes
        if (attr[0] == '-' && allowedAttributes.find(attr) == allowedAttributes.end()) {
            std::cout << shape << " cannot have attribute: " << attr << std::endl;
            return false;
        }
    }

    return true;
}


class ShapeRegistry {
public:
    ShapeRegistry();
    bool isValidShape(const std::string& shapeName);

private:
    std::vector<CommandType> ValidShapes;
};

ShapeRegistry::ShapeRegistry() :
    ValidShapes{ "rectangle", "line", "circle", "trapezoid", "elipse"} {}

bool ShapeRegistry::isValidShape(const std::string& shapeName) {
    for (const auto& cmd : ValidShapes) {
        if (shapeName == cmd) {
            return true;
        }
    }
    return false;
}



class InputTaker {
public:
    std::istream& readInput(std::istream&, std::string&);
};


std::istream& InputTaker::readInput(std::istream& input, std::string& line) {
    std::getline(input, line);
    return input;
}




class Tokenizer {
public:
    void takeTokens(const std::string& input);
    std::vector<std::string> getTokens();

private:
    std::vector<std::string> tokens;
};

void Tokenizer::takeTokens(const std::string& input) {
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
}

std::vector<std::string> Tokenizer::getTokens() {
    return tokens;
}



class Parser {
public:
    Parser(const std::string& input, CommandRegistry& registry);

    std::string getCommand() const;
    std::vector<std::string> getArguments() const;
    std::string getRestOfTheLine() const;
    bool isValidCommand() const;

    void parse();

private:
    std::string input;
    CommandRegistry& registry;
    std::string command;  // Store the valid command
    std::vector<std::string> arguments;  // Store the arguments
    std::string restOfTheLine;  // Store the rest of the line
    bool validCommand;  // Flag to indicate if the command is valid
};

Parser::Parser(const std::string& input, CommandRegistry& registry) :
    input(input), registry(registry), validCommand(false) {}

std::string Parser::getCommand() const {
    return command;
}

std::vector<std::string> Parser::getArguments() const {
    return arguments;
}

std::string Parser::getRestOfTheLine() const {
    return restOfTheLine;
}

bool Parser::isValidCommand() const {
    return validCommand;
}

void Parser::parse() {
    Tokenizer tokenizer;
    tokenizer.takeTokens(input);
    std::vector<std::string> tokens = tokenizer.getTokens();

    if (!tokens.empty()) {
        std::string possibleCommand = tokens[0];
        if (registry.isValidCommand(possibleCommand)) {
            validCommand = true;
            command = possibleCommand;

            // Store the arguments and the rest of the line
            arguments.clear();
            restOfTheLine.clear();
            for (size_t i = 1; i < tokens.size(); ++i) {
                if (i == 1) {
                    restOfTheLine += tokens[i];
                }
                else {
                    restOfTheLine += " " + tokens[i];
                }
                arguments.push_back(tokens[i]);
            }
        }
        else {
            std::cerr << "Invalid command." << std::endl;
        }
    }
}


class QuitExecutor {
public:
    void execute();
};

void QuitExecutor::execute() {
    exit(EXIT_FAILURE);
}






class AddExecutor {
public:
    AddExecutor(const std::string& restOfTheLine);
    void addToMap(std::map<int, std::string>& itemsMap);

private:
    std::string addedItems;
};

AddExecutor::AddExecutor(const std::string& restOfTheLine) {
    std::istringstream iss(restOfTheLine);
    std::string token;
    while (iss >> token) {
        if (token[0] != '-')
            addedItems += token + " ";
    }
}

void AddExecutor::addToMap(std::map<int, std::string>& itemsMap) {
    static int index = 1; // Static to keep track of the index across invocations
    itemsMap[index++] = addedItems;
}






class DisplayExecutor {
public:
    DisplayExecutor(const std::map<int, std::string>& itemsMap);
    void execute();

private:
    const std::map<int, std::string>& itemsMap;
};

DisplayExecutor::DisplayExecutor(const std::map<int, std::string>& itemsMap) : itemsMap(itemsMap) {}

void DisplayExecutor::execute() {
    std::cout << "Displaying added items:" << std::endl;
    for (const auto& entry : itemsMap) {
        std::cout << entry.first << " " << entry.second << std::endl;
    }
}



class RemoveExecutor {
public:
    RemoveExecutor(int index);
    void removeFromMap(std::map<int, std::string>& itemsMap);

private:
    int itemIndex;
};

RemoveExecutor::RemoveExecutor(int index) : itemIndex(index) {}

void RemoveExecutor::removeFromMap(std::map<int, std::string>& itemsMap) {
    auto it = itemsMap.find(itemIndex);
    if (it != itemsMap.end()) {
        itemsMap.erase(it);
        std::cout << "Item with index " << itemIndex << " removed." << std::endl;
    }
    else {
        std::cerr << "Item with index " << itemIndex << " not found. No item removed." << std::endl;
    }
}


class SaveExecutor {
public:
    SaveExecutor(const std::string& filePath, const std::map<int, std::string>& itemsMap);

    void execute();

private:
    std::string filePath;
    const std::map<int, std::string>& itemsMap;
};

SaveExecutor::SaveExecutor(const std::string& filePath, const std::map<int, std::string>& itemsMap)
    : filePath(filePath), itemsMap(itemsMap) {}

void SaveExecutor::execute() {
    std::ofstream outputFile(filePath);

    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file for saving." << std::endl;
        return;
    }

    // Write the content of the itemsMap to the file
    for (const auto& entry : itemsMap) {
        outputFile << entry.first << " " << entry.second << std::endl;
    }

    std::cout << "Content saved to file: " << filePath << std::endl;

    outputFile.close();
}


class Controller {
public:
    void run();
};

void Controller:: run() {
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


int main() {
    Controller obj;
    obj.run();
    return 0;
}
