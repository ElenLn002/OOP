#include "CommandValidator.hpp"
#include "Tokenizer.hpp"

CommandValidator::CommandValidator(CommandRegistry& cmdRegistry, ShapeRegistry& shapeRegistry, AttributeRegistry& attrRegistry) :
    cmdRegistry(cmdRegistry), shapeRegistry(shapeRegistry), attrRegistry(attrRegistry) {}

bool CommandValidator::isValidCommand(const std::string& input) {
    Tokenizer tokenizer;
    tokenizer.takeTokens(input);
    std::vector<std::string> tokens = tokenizer.getTokens();

    if (tokens.size() < 2) {
        return false;
    }

    if (!cmdRegistry.isValidCommand(tokens[0])) {
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
