#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <fstream>
#include <stdexcept>
#include <regex>
#include <sstream>

std::string trim(const std::string& str) {
	size_t first = str.find_first_not_of(" ");
	if (std::string::npos == first) {
		return str;
	}
	size_t last = str.find_last_not_of(" ");
	return str.substr(first, (last - first + 1));
}

class Tokenizer{
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
	bool isValidCommand(std::string& cmd);

private:
	std::vector<std::string> validCommands;
};

CommandRegistry::CommandRegistry():
	validCommands{"Add", "Remove", "Save", "Display", "List", "Change", "Load", "Quit"} {}

bool CommandRegistry:: isValidCommand(std::string& commandName){
	for (auto input : validCommands) {
		if (commandName == input) {
			return true;
		}
	}
	return false;
}

class Parser {
public:
	Parser(const std::string& input, CommandRegistry& registry);

	std::string getCommand() const;
	std::vector<std::string> getItems() const;
	std::string getRestOfLine() const;
	bool getValidCommand() const;

	void parse();

private:
	std::string input;
	CommandRegistry& registry;
	std::string command;  // Store the valid command
	std::vector<std::string> items;  // Store the arguments
	std::string restOfLine;  // Store the rest of the line
	bool validCommand;  // Flag to indicate if the command is valid
};


Parser::Parser(const std::string& input, CommandRegistry& registry) : 
	input(input), registry(registry), validCommand(false){}

std::string Parser::getCommand() const {
	return command;
}

std::vector<std::string> Parser:: getItems() const {
	return items;
}

std::string Parser::getRestOfLine() const {
	return restOfLine;
}

bool Parser::getValidCommand() const{
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
	bool isValidShape(const std::string& shape);  // Accept a const reference

private:
	std::vector<std::string> validShapes;
};

ShapeRegistry::ShapeRegistry() :
	validShapes{ "rectangle", "ellipse", "line", "triangle", "trapezoid" } {}

bool ShapeRegistry::isValidShape(const std::string& inputShape) {  // Accept a const reference
	for (const auto& input : validShapes) {
		if (inputShape == input) {
			return true;
		}
	}
	return false;
}

class CommandValidator {
public:
	CommandValidator(CommandRegistry& registry, ShapeRegistry& shapeRegistry);

	bool validateCommand(const Parser& parser, std::map<int, std::string>& itemsMap);

private:
	CommandRegistry& registry;
	ShapeRegistry& shapeRegistry;

	bool validateColor(const std::string& color);
	bool validateCoordinate(const std::string& coord);
	bool validateSlide(const std::string& slide, int lastID);
};

CommandValidator::CommandValidator(CommandRegistry& registry, ShapeRegistry& shapeRegistry)
	: registry(registry), shapeRegistry(shapeRegistry) {}

bool CommandValidator::validateCommand(const Parser& parser, std::map<int, std::string>& itemsMap) {
	if (!parser.getValidCommand()) {
		std::cerr << "Invalid command." << std::endl;
		return false;
	}

	if (parser.getCommand() == "Add") {
		if (parser.getItems().empty()) {
			std::cerr << "Add command requires item attributes." << std::endl;
			return false;
		}

		std::set<std::string> validAttributes{ "-colour", "-TL", "-RB", "-slide" };
		std::string prevAttribute;
		int lastID = itemsMap.empty() ? 0 : itemsMap.rbegin()->first;

		for (const std::string& attribute : parser.getItems()) {
			if (validAttributes.find(attribute) == validAttributes.end()) {
				std::cerr << "Invalid attribute: " << attribute << std::endl;
				return false;
			}

			if (attribute == "-colour") {
				if (!validateColor(parser.getRestOfLine())) {
					std::cerr << "Invalid colour: " << parser.getRestOfLine() << std::endl;
					return false;
				}
			}
			else if (attribute == "-TL" || attribute == "-RB") {
				if (!validateCoordinate(parser.getRestOfLine())) {
					std::cerr << "Invalid coordinate format: " << parser.getRestOfLine() << std::endl;
					return false;
				}
			}
			else if (attribute == "-slide") {
				if (!validateSlide(parser.getRestOfLine(), lastID)) {
					std::cerr << "Invalid slide number: " << parser.getRestOfLine() << std::endl;
					return false;
				}
			}

			prevAttribute = attribute;
		}
	}

	// Implement validation logic for other commands as needed

	return true;
}

bool CommandValidator::validateColor(const std::string& color) {
	std::set<std::string> validColors{ "red", "green", "yellow", "blue", "dark blue" };
	return validColors.count(color) > 0;
}

bool CommandValidator::validateCoordinate(const std::string& coord) {
	if (coord.size() < 5 || coord[0] != '(' || coord[coord.size() - 1] != ')' || coord.find(';') == std::string::npos) {
		return false;
	}

	std::string x_part = coord.substr(1, coord.find(';') - 1);
	std::string y_part = coord.substr(coord.find(';') + 2, coord.size() - 2 - coord.find(';'));

	try {
		int x = std::stoi(x_part);
		int y = std::stoi(y_part);

		return true;
	}
	catch (const std::invalid_argument&) {
		return false;
	}
}

bool CommandValidator::validateSlide(const std::string& slide, int lastID) {
	try {
		int slideNumber = std::stoi(slide);
		return slideNumber == (lastID + 1) || slideNumber <= lastID;
	}
	catch (const std::invalid_argument&) {
		return false;
	}
}


class CommandExecutor{
public:
	virtual void execute(std::map<int, std::string>& itemsMap) = 0;
};

class AddExecutor : public CommandExecutor{
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

class RemoveExecutor : public CommandExecutor{
public:
	RemoveExecutor(int ID);
	void execute(std::map<int, std::string>& itemsMap) override;

private:  
	int itemID;
};

RemoveExecutor::RemoveExecutor(int ID): itemID(ID){}

void RemoveExecutor::execute(std::map<int, std::string>& itemsMap) {
	auto it = itemsMap.find(itemID);
	if (it != itemsMap.end()) {
		itemsMap.erase(it);
	}
	else {
		std::cerr << "ID not found" << std::endl;
	}
}

class ChangeExecutor : public CommandExecutor{
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

class SaveExecutor : public CommandExecutor{
public:
	SaveExecutor(std::string filePath, std::map<int, std::string>& itemsMap);
	void execute(std::map<int, std::string>& itemsMap) override;

private:
	std::string filePath;
	std::map<int, std::string>& itemsMap;

};

SaveExecutor::SaveExecutor(std::string filePath, std::map<int, std::string>& itemsMap):
	filePath(filePath), itemsMap(itemsMap){}

void SaveExecutor::execute(std::map<int, std::string>& itemsMap) {
	std::ofstream outputFile(filePath);
	if (!outputFile.is_open()) {
		std::cerr << "Unable to open file";
	}

	for (const auto& entry : itemsMap) {
		outputFile << entry.first << " " << entry.second << std::endl;
	}

	std::cout << "Content saved to file: " << filePath << std::endl;
	outputFile.close();
}

class DisplayExecutor : public CommandExecutor{
public:
	DisplayExecutor(int ID, std::string attributes);
	void execute(std::map<int, std::string>& itemsMap) override;

private:
	int itemID;
	std::string ItemAttributes;
};

DisplayExecutor::DisplayExecutor(int ID, std::string attributes) :
itemID(ID), ItemAttributes(attributes) {}

void DisplayExecutor::execute(std::map<int, std::string>& itemsMap) {
	auto it = itemsMap.find(itemID);
	if (it != itemsMap.end()) {
		auto entry = itemsMap.begin();
		std::cout << entry->first << " " << entry->second << std::endl;
	}
	else {
		std::cerr << "ID not found" << std::endl;
	}
}

class ListExecutor : public CommandExecutor {
public:
	ListExecutor(const std::map<int, std::string>& itemsMap);
	void execute(std::map<int, std::string>& itemsMap) override;

private:
	const std::map<int, std::string>& itemsMap;
};

ListExecutor::ListExecutor(const std::map<int, std::string>& itemsMap):
	itemsMap(itemsMap) {}

void ListExecutor::execute(std::map<int, std::string>& itemsMap) {
	for (const auto& entry : itemsMap) {
		std::cout << entry.first << " " << entry.second << std::endl;
	}
}

class Controller {
public:
	Controller(CommandRegistry& cmdRegistry, ShapeRegistry& shpRegistry, CommandValidator& cmdValidator, bool flag);
	void run();

private:
	std::map<int, std::string> itemsMap;
	CommandRegistry& commandRegistry;
	ShapeRegistry& shapeRegistry;
	CommandValidator& commandValidator;
	bool flag;

	bool validateCommand(const Parser& parser);
	void executeCommand(const Parser& parser);
};

Controller::Controller(CommandRegistry& cmdRegistry, ShapeRegistry& shpRegistry, CommandValidator& cmdValidator, bool flag)
	: commandRegistry(cmdRegistry), shapeRegistry(shpRegistry), commandValidator(cmdValidator), flag(true) {}

void Controller::run() {
	while (flag) {

		std::cout << "Enter a command: ";
		std::string userInput;
		std::getline(std::cin, userInput);

		Parser parser(userInput, commandRegistry);
		parser.parse();

		executeCommand(parser);
	}
}



bool Controller::validateCommand(const Parser& parser) {
	if (!parser.getValidCommand()) {
		std::cerr << "Invalid command." << std::endl;
		return false;
	}

	if (parser.getCommand() == "Add") {
		if (!parser.getItems().empty() && parser.getItems()[0] == "shape") {
			// Check if the shape is valid
			if (!shapeRegistry.isValidShape(parser.getRestOfLine())) {
				std::cerr << "Invalid shape: " << parser.getRestOfLine() << std::endl;
				return false;
			}
		}
		else {
			std::cerr << "Add command requires 'shape' attribute." << std::endl;
			return false;
		}

		if (!commandValidator.validateCommand(parser, itemsMap)) {
			return false;
		}
	}
	return true;
}

void Controller::executeCommand(const Parser& parser) {
	if (!validateCommand(parser)) {
		return;
	}
	
	else if (parser.getCommand() == "Display") {
		// Create and execute the Display command logic
		std::cout << "Displaying item: " << parser.getRestOfLine() << std::endl;
	}
	else if (parser.getCommand() == "Quit") {
		flag = false;
	}
	else if (parser.getCommand() == "Remove") {
		// Create and execute the Remove command logic
		if (!parser.getRestOfLine().empty()) {
			int indexToRemove;
			try {
				indexToRemove = std::stoi(parser.getRestOfLine());
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
	else if (parser.getCommand() == "Save") {
		// Create and execute the Save command logic
		if (!parser.getRestOfLine().empty()) {
			std::string filePath = parser.getRestOfLine();
			SaveExecutor saveExecutor(filePath, itemsMap);
			saveExecutor.execute(itemsMap);
		}
		else {
			std::cerr << "Invalid arguments for Save command." << std::endl;
		}
	}
	else if (parser.getCommand() == "Change") {
		// Create and execute the Change command logic
		std::istringstream argStream(parser.getRestOfLine());
		int indexToChange;
		argStream >> indexToChange;
		std::string newAttributes = parser.getRestOfLine().substr(parser.getRestOfLine().find_first_of(" ") + 1);

		if (argStream && !newAttributes.empty()) {
			ChangeExecutor changeExecutor(indexToChange, newAttributes);
			changeExecutor.execute(itemsMap);
		}
		else {
			std::cerr << "Invalid arguments for Change command." << std::endl;
		}
	}
	else if (parser.getCommand() == "List") {
		// Create and execute the List command logic
		ListExecutor listExecutor(itemsMap);
		listExecutor.execute(itemsMap);
	}
	
}

int main() {
	CommandRegistry commandRegistry;
	ShapeRegistry shapeRegistry;
	CommandValidator commandValidator(commandRegistry, shapeRegistry);
	Controller controller(commandRegistry, shapeRegistry, commandValidator, true);
	controller.run();

	return 0;
}
