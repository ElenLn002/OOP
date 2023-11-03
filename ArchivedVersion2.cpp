#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <sstream>


std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" ");
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" ");
    return str.substr(first, (last - first + 1));
}

class Tokenizer {
public:
    void takeTokens(const std::string input);
    std::vector<std::string> getTokens() const;

private:
    std::string token;
    std::vector<std::string> tokens;
};

void Tokenizer::takeTokens(const std::string input) {
    std::string token;
    std::istringstream iss(input);
    while (iss >> token) {
        tokens.push_back(token);
    }
}

std::vector<std::string> Tokenizer::getTokens() const {
    return tokens;
}

class CommandRegistry {
public:
    CommandRegistry();
    bool isValidCommand(const std::string& cmd);

private:
    std::vector<std::string> validCommands;
};

CommandRegistry::CommandRegistry() :
    validCommands{ "Add", "Remove", "Save", "Display", "List", "Change", "Quit" } {}

bool CommandRegistry::isValidCommand(const std::string& commandName) {
    for (const auto& input : validCommands) {
        if (commandName == input) {
            return true;
        }
    }
    return false;
}

class AttributeRegistry {
public:
    AttributeRegistry();
    bool areValidAttributes(const std::vector<std::string>& attr);

private:
    std::vector<std::string> validAttributes;
};

AttributeRegistry::AttributeRegistry() :
    validAttributes{ "-colour", "-TL", "-RB", "-slide" } {}

bool AttributeRegistry::areValidAttributes(const std::vector<std::string>& attrs) {
    for (const std::string& attr : attrs) {
        bool isValid = false;
        for (const std::string& validAttr : validAttributes) {
            if (attr == validAttr) {
                isValid = true;
                break;
            }
        }
        if (!isValid) {
            return false;  
        }
    }
    return true;  // All attributes are valid.
}

class Parser {
public:
    Parser(const std::string& input, CommandRegistry& registry);


    void parse();

private:
    std::string input;
    CommandRegistry& registry;
    std::string command;  
    std::vector<std::string> items;  
    std::string restOfLine;  
    bool validCommand;  
};

Parser::Parser(const std::string& input, CommandRegistry& registry) :
    input(input), registry(registry), validCommand(false) {
    parse();
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
        }

        items.clear();
        restOfLine.clear();
        for (size_t i = 1; i < tokens.size(); ++i) {
            if (i == 1) {
                restOfLine += tokens[i];
            }
            else {
                restOfLine += " " + tokens[i];
            }
            items.push_back(tokens[i]);
        }
    }
}

class ShapeRegistry {
public:
    ShapeRegistry();
    bool isValidShape(const std::string& shape);

private:
    std::vector<std::string> validShapes;
};

ShapeRegistry::ShapeRegistry() :
    validShapes{ "rectangle", "ellipse", "line", "triangle", "trapezoid" } {}

bool ShapeRegistry::isValidShape(const std::string& inputShape) {
    for (const auto& input : validShapes) {
        if (inputShape == input) {
            return true;
        }
    }
    return false;
}

class CommandValidator {
public:
    CommandValidator(CommandRegistry& cmdRegistry, ShapeRegistry& shapeRegistry, AttributeRegistry& attrRegistry);
    bool isValidCommand(const std::string& input);

private:
    CommandRegistry& cmdRegistry;
    ShapeRegistry& shapeRegistry;
    AttributeRegistry& attrRegistry;
};

CommandValidator::CommandValidator(CommandRegistry& cmdRegistry, ShapeRegistry& shapeRegistry, AttributeRegistry& attrRegistry) :
    cmdRegistry(cmdRegistry), shapeRegistry(shapeRegistry), attrRegistry(attrRegistry) {}

bool CommandValidator::isValidCommand(const std::string& input) {
    Tokenizer tokenizer;
    tokenizer.takeTokens(input);
    std::vector<std::string> tokens = tokenizer.getTokens();

    // Check if there are at least two tokens (command and shape)
    if (tokens.size() < 2) {
        return false;
    }

    // Check if the first token is a valid command
    if (!cmdRegistry.isValidCommand(tokens[0])) {
        return false;
    }

    // Check if the second token is a valid shape
    if (!shapeRegistry.isValidShape(tokens[1])) {
        return false;
    }

    // Check if other tokens starting with dash are valid attributes
    std::vector<std::string> attributes(tokens.begin() + 2, tokens.end());
    if (!attrRegistry.areValidAttributes(attributes)) {
        return false;
    }

    return true;
}

class Item {
public:
    Item(int ID, const std::string& shape, const std::string& geometry, const std::string& attributes);

    std::string getShape() const;
    std::string getGeometry() const;
    std::string getAttributes() const;
    
    void setAttributes(const std::string& attributes);
    void setGeometry(const std::string& geometry);

private:
    std::string attributes;
    std::string shape;
    std::string geometry;
    int ID;
};

Item::Item(int ID, const std::string& shape, const std::string& geometry, const std::string& attributes) :
    ID(ID), shape(shape), geometry(geometry), attributes(attributes) {}

std::string Item::getShape() const {
    return shape;
}

std::string Item::getGeometry() const {
    return geometry;
}

std::string Item::getAttributes() const {
    return attributes;
}

void Item::setAttributes(const std::string& attributes) {
    this->attributes = attributes;
}

void Item::setGeometry(const std::string& geometry) {
    this->geometry = geometry;
}

class Slide {
public:
    Slide()=default;

    void addItem(const std::shared_ptr<Item>& item);
    const std::vector<std::shared_ptr<Item>>& getItems() const;

private:
    std::vector<std::shared_ptr<Item>> items;
};


void Slide::addItem(const std::shared_ptr<Item>& item) {
    items.push_back(item);
}

const std::vector<std::shared_ptr<Item>>& Slide::getItems() const {
    return items;
}

class Document {
public:
    Document()=default;

    void addSlide(const std::shared_ptr<Slide>& slide);
    const std::vector<std::shared_ptr<Slide>>& getSlides() const;

private:
    std::vector<std::shared_ptr<Slide>> slides;
};

void Document::addSlide(const std::shared_ptr<Slide>& slide) {
    slides.push_back(slide);
}

const std::vector<std::shared_ptr<Slide>>& Document::getSlides() const {
    return slides;
}


class CommandExecutor {
public:
    virtual void execute(std::map<int, std::string>& itemsMap) = 0;
};

class AddExecutor : public CommandExecutor {
public:
    AddExecutor(std::string restOfLine);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    std::string addedAttributes;
};

AddExecutor::AddExecutor(std::string restOfLine) {
    std::istringstream iss(restOfLine);
    std::string token;
    while (iss >> token) {
        if (token[0] != '-') {
            addedAttributes += token + " ";
        }
    }
}

void AddExecutor::execute(std::map<int, std::string>& itemsMap) {
    static int ID = 1;
    itemsMap[ID++] = addedAttributes;
}

class RemoveExecutor : public CommandExecutor {
public:
    RemoveExecutor(int ID);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    int itemID;
};

RemoveExecutor::RemoveExecutor(int ID) : itemID(ID) {}

void RemoveExecutor::execute(std::map<int, std::string>& itemsMap) {
    auto it = itemsMap.find(itemID);
    if (it != itemsMap.end()) {
        itemsMap.erase(it);
    }
    else {
        std::cerr << "ID not found" << std::endl;
    }
}

class ChangeExecutor : public CommandExecutor {
public:
    ChangeExecutor(int ID, std::string& newAttributes);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    int itemID;
    std::string newAttributes;
};

ChangeExecutor::ChangeExecutor(int ID, std::string& newAttributes) :
    itemID(ID), newAttributes(newAttributes) {}

void ChangeExecutor::execute(std::map<int, std::string>& itemsMap) {
    auto it = itemsMap.find(itemID);
    if (it != itemsMap.end()) {
        it->second = newAttributes;
    }
    else {
        std::cerr << "ID not found" << std::endl;
    }
}

class SaveExecutor : public CommandExecutor {
public:
    SaveExecutor(std::string filePath, std::map<int, std::string>& itemsMap);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    std::string filePath;
    std::map<int, std::string>& itemsMap;
};

SaveExecutor::SaveExecutor(std::string filePath, std::map<int, std::string>& itemsMap) :
    filePath(filePath), itemsMap(itemsMap) {}

void SaveExecutor::execute(std::map<int, std::string>& itemsMap) {
    std::ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }

    for (const auto& entry : itemsMap) {
        outputFile << entry.first << " " << entry.second << std::endl;
    }

    std::cout << "Content saved to file: " << filePath << std::endl;
    outputFile.close();
}

class DisplayExecutor : public CommandExecutor {
public:
    DisplayExecutor(int ID, const std::map<int, std::string>& itemsMap);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    int itemID;
    const std::map<int, std::string>& itemsMap;
};

DisplayExecutor::DisplayExecutor(int ID, const std::map<int, std::string>& itemsMap)
    : itemID(ID), itemsMap(itemsMap) {}

void DisplayExecutor::execute(std::map<int, std::string>& itemsMap) {
    auto it = itemsMap.find(itemID);
    if (it != itemsMap.end()) {
        std::cout << "ID: " << itemID << " Shape: " << it->second << std::endl;
    }
    else {
        std::cerr << "ID not found: " << itemID << std::endl;
    }
}

class ListExecutor : public CommandExecutor {
public:
    ListExecutor(const std::map<int, std::string>& itemsMap);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    const std::map<int, std::string>& itemsMap;
};

ListExecutor::ListExecutor(const std::map<int, std::string>& itemsMap) :
    itemsMap(itemsMap) {}

void ListExecutor::execute(std::map<int, std::string>& itemsMap) {
    for (const auto& entry : itemsMap) {
        std::cout << entry.first << " " << entry.second << std::endl;
    }
}

class Controller {
public:
    void run();

private:
    std::map<int, std::string> itemsMap;

    void handleAdd(const std::string& restOfTheLine);
    void handleDisplay();
    void handleRemove(const std::string& restOfTheLine);
    void handleSave(const std::string& restOfTheLine);
    void handleChange(const std::string& restOfTheLine);
    void handleList();
};

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
        // Create a DisplayExecutor with the user-provided ID
        DisplayExecutor displayExecutor(displayID, itemsMap);

        // Execute the DisplayExecutor
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

int main() {
    Controller controller;
    controller.run();

    return 0;
}
