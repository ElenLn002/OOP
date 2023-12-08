#include "Parser.hpp"

Parser::Parser(const std::string& input, CommandRegistry& registry)
    : input(input), registry(registry), validCommand(false) {
    parseInput();
}

void Parser::parseInput() {
    std::istringstream iss(input);
    Tokenizer tokenizer;
    tokenizer.takeTokens(iss);  // Pass the stream to takeTokens
    std::vector<std::string> tokens = tokenizer.getTokens();

    if (!tokens.empty()) {
        command = tokens[0];
        validCommand = registry.isValidCommand(command);

        // Clear the attributes map before populating it
        attributesMap.clear();

        // Assuming attributes start from the second token onwards
        for (size_t i = 1; i < tokens.size(); ++i) {
            // Store each attribute in the unordered map with its corresponding index
            attributesMap[i - 1] = tokens[i];
        }
    }
}

std::unique_ptr<Command> Parser::parse() {
    if (!validCommand) {
        std::cout << "Invalid command." << std::endl;
        return nullptr;
    }

    // Create the appropriate command based on the parsed input
    std::unique_ptr<Command> commandObj;
    if (command == "Add") {
        commandObj = std::make_unique<Add>();
    }
    else if (command == "Remove") {
        commandObj = std::make_unique<Remove>();
    }
    else if (command == "Change") {
        commandObj = std::make_unique<Change>();
    }
    else if (command == "Display") {
        commandObj = std::make_unique<Display>();
    }
    else if (command == "List") {
        commandObj = std::make_unique<List>();
    }
    else if (command == "Save") {
        commandObj = std::make_unique<Save>();
    }
    else if (command == "Load") {
        commandObj = std::make_unique<Load>();
    }
    else if (command == "Quit") {
        commandObj = std::make_unique<Quit>();
    }
    else {
        std::cout << "Unknown command." << std::endl;
        return nullptr;
    }

    return commandObj;
}
