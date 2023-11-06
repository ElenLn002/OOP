#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <any>
#include <memory>
#include <iterator>
#include <unordered_map>
#include <utility>
#include <fstream>
#include <sstream>
#include <stack>

using shapeType = std::string;
using actionType = std::string;
using slideItr = std::map<std::string, std::any>;

static const int INITIAL_ITEM_ID = 1;
static const size_t SECOND_ELEMENT_INDEX = 1;



std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" ");
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" ");
    return str.substr(first, (last - first + 1));
}


class ResultPrinter {
public:
    void printItem(int itemID, const std::string& itemAttributes) {
        std::cout <<  itemID << " " << itemAttributes << std::endl;
    }

    void printItems(const std::map<int, std::string>& itemsMap) {
        for (const auto& entry : itemsMap) {
            printItem(entry.first, entry.second);
        }
    }
};

ResultPrinter resultPrinter;  


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

    // Add error handling to check for unexpected input here
    if (!iss.eof()) {
        std::cerr << "Error: Unexpected input in Tokenizer." << std::endl;
    }
}

std::vector<std::string> Tokenizer::getTokens() const {
    return tokens;
}

class ActionRegistry {
public: 
    ActionRegistry();
    bool isValidAction(const actionType& act);

private:
    std::vector<actionType> validActions;
};

ActionRegistry::ActionRegistry() :
    validActions { "Undo", "Redo" }
{};

bool ActionRegistry::isValidAction(const actionType& actionName) {
    for (const auto& input : validActions) {
        if (actionName == input) {
            return true;
        }
    }
    return false;
}

class CommandRegistry {
public:
    CommandRegistry();
    bool isValidCommand(const std::string& cmd);

private:
    std::vector<std::string> validCommands;
};

CommandRegistry::CommandRegistry() :
    validCommands{ "Add", "Remove", "Save", "Display", "List", "Change", "Quit", "Undo", "Redo"} {}

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
    validAttributes{ "-colour", "-TL", "-RB", "-slide", "-fcolour", "-lcolour", "-style"} {}

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

    bool isValidCommand() const;
    std::string getCommand() const;
    std::string getRestOfLine() const;

private:
    std::string input;
    CommandRegistry& registry;
    std::string command;
    std::string restOfLine;
    bool validCommand;

    void parse();
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
        command = tokens[0];
        validCommand = registry.isValidCommand(command);

        restOfLine.clear();
        for (size_t i = 1; i < tokens.size(); ++i) {
            if (i == SECOND_ELEMENT_INDEX) {
                restOfLine += tokens[i];
            }
            else {
                restOfLine += " " + tokens[i];
            }
        }
    }
}

bool Parser::isValidCommand() const {
    return validCommand;
}

std::string Parser::getCommand() const {
    return command;
}

std::string Parser::getRestOfLine() const {
    return restOfLine;
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

class ActionInterface {
public:
    virtual void execute() = 0;
};

class Undo : public ActionInterface {
public:
    Undo(std::stack<std::map<int, std::string>>& undoStack, std::stack<std::map<int, std::string>>& redoStack, std::map<int, std::string>& itemsMap);
    void execute() override;

private:
    std::stack<std::map<int, std::string>>& undoStack;
    std::stack<std::map<int, std::string>>& redoStack;
    std::map<int, std::string>& itemsMap;
};

class Redo : public ActionInterface {
public:
    Redo(std::stack<std::map<int, std::string>>& undoStack, std::stack<std::map<int, std::string>>& redoStack, std::map<int, std::string>& itemsMap);
    void execute() override;

private:
    std::stack<std::map<int, std::string>>& undoStack;
    std::stack<std::map<int, std::string>>& redoStack;
    std::map<int, std::string>& itemsMap;
};

Undo::Undo(std::stack<std::map<int, std::string>>& undoStack, std::stack<std::map<int, std::string>>& redoStack, std::map<int, std::string>& itemsMap)
    : undoStack(undoStack), redoStack(redoStack), itemsMap(itemsMap) {}

Redo::Redo(std::stack<std::map<int, std::string>>& undoStack, std::stack<std::map<int, std::string>>& redoStack, std::map<int, std::string>& itemsMap)
    : undoStack(undoStack), redoStack(redoStack), itemsMap(itemsMap) {}

void Undo::execute() {
    if (!undoStack.empty()) {
        redoStack.push(itemsMap);
        itemsMap = undoStack.top();
        undoStack.pop();
        std::cout << "Undo operation performed." << std::endl;
    }
    else {
        std::cout << "No actions to undo." << std::endl;
    }
}

void Redo::execute() {
    if (!redoStack.empty()) {
        undoStack.push(itemsMap);
        itemsMap = redoStack.top();
        redoStack.pop();
        std::cout << "Redo operation performed." << std::endl;
    }
    else {
        std::cout << "No actions to redo." << std::endl;
    }
}




class CommandValidator {
public:
    CommandValidator(CommandRegistry& cmdRegistry, ShapeRegistry& shapeRegistry, AttributeRegistry& attrRegistry, ActionRegistry& actRegistry);
    bool isValidCommand(const std::string& input);

private:
    CommandRegistry& cmdRegistry;
    ShapeRegistry& shapeRegistry;
    AttributeRegistry& attrRegistry;
    ActionRegistry& actRegistry;
};

CommandValidator::CommandValidator(CommandRegistry& cmdRegistry, ShapeRegistry& shapeRegistry, AttributeRegistry& attrRegistry, ActionRegistry& actRegistry) :
    cmdRegistry(cmdRegistry), shapeRegistry(shapeRegistry), attrRegistry(attrRegistry), actRegistry(actRegistry) {}

bool CommandValidator::isValidCommand(const std::string& input) {
    Tokenizer tokenizer;
    tokenizer.takeTokens(input);
    std::vector<std::string> tokens = tokenizer.getTokens();

    if (tokens.size() < 2) {
        return false;
    }

    if (!cmdRegistry.isValidCommand(tokens[0]) || !actRegistry.isValidAction(tokens[0])) {
        std::cerr << "Error: Invalid command '" << tokens[0] << "'." << std::endl;
        return false;
    }

    if (!shapeRegistry.isValidShape(tokens[1])) {
        return false;
    }

    std::vector<std::string> attributes(tokens.begin() + 2, tokens.end());
    if (!attrRegistry.areValidAttributes(attributes)) {
        return false;
    }

    return true;
}

class Item {
public:
    Item(int ID, const shapeType& shape, const std::string& pos, const std::string& attributes);

    shapeType getShape() const;
    std::string getPosition() const;
    std::string getAttributes() const;
    int getID() const;
    
    void setAttributes(const std::string& attributes);
    void setPosition(const std::string& pos);

private:
    std::string attributes;
    shapeType shape;
    std::string pos;
    int ID;
};

int Item::getID() const {
    return ID;
}

Item::Item(int ID, const shapeType& shape, const std::string& pos, const std::string& attributes) :
    ID(ID), shape(shape), pos(pos), attributes(attributes) {}

shapeType Item::getShape() const {
    return shape;
}

std::string Item::getPosition() const { //I just do not like the name geometry
    return pos;
}

std::string Item::getAttributes() const {
    return attributes;
}

void Item::setAttributes(const std::string& attributes) {
    this->attributes = attributes;
}

void Item::setPosition(const std::string& pos) {
    this->pos = pos;
}

class Slide {
public:
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
    void addSlide(const std::shared_ptr<Slide>& slide);
    std::shared_ptr<Slide> getSlide(int slideID) const;

private:
    std::vector<std::shared_ptr<Slide>> slides;
};

void Document::addSlide(const std::shared_ptr<Slide>& slide) {
    slides.push_back(slide);
}

std::shared_ptr<Slide> Document::getSlide(int slideID) const {
    if (slideID > 0 && slideID <= slides.size()) {
        return slides[slideID - 1];
    }
    return nullptr;
}

class  ActionExecutor {
public:
    virtual void execute() = 0;
};


class RenderingInterface {
public:
    virtual void execute(std::map<int, std::string>& itemsMap) = 0;
};

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
    static int ID = INITIAL_ITEM_ID;
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

        // Create a new map with adjusted IDs
        std::map<int, std::string> newItemsMap;
        for (const auto& item : itemsMap) {
            if (item.first > itemID) {
                newItemsMap[item.first - 1] = item.second;
            }
            else {
                newItemsMap[item.first] = item.second;
            }
        }

        itemsMap = newItemsMap;
    }
    else {
        std::cerr << "ID not found: " << itemID << std::endl;
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

class DisplayExecutor : public RenderingInterface {
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
            resultPrinter.printItem(itemID, it->second);
        }
        else {
            std::cerr << "ID not found: " << itemID << std::endl;
        }
    
}



class ListExecutor : public RenderingInterface {
public:
    ListExecutor(const std::map<int, std::string>& itemsMap);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    const std::map<int, std::string>& itemsMap;
};

ListExecutor::ListExecutor(const std::map<int, std::string>& itemsMap)
    : itemsMap(itemsMap) {}

void ListExecutor::execute(std::map<int, std::string>& itemsMap) {
    resultPrinter.printItems(itemsMap); // Delegate the printing to ResultPrinter
}

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
    void handleChange(const std::string& restOfTheLine);
    void handleList();
    void handleUndo();
    void handleRedo();
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

int main() {
    Controller controller;
    controller.run();

    return 0;
}
