#ifndef COMMANDVALIDATOR_HPP
#define COMMANDVALIDATOR_HPP

#include "CommandRegistry.hpp"
#include "ShapeRegistry.hpp"
#include "AttributeRegistry.hpp"

#include <string>

class CommandValidator {
public:
    CommandValidator(CommandRegistry& cmdRegistry, ShapeRegistry& shapeRegistry, AttributeRegistry& attrRegistry);
    bool isValidCommand(const std::string& input);

private:
    CommandRegistry& cmdRegistry;
    ShapeRegistry& shapeRegistry;
    AttributeRegistry& attrRegistry;
};

#endif //COMMANDVALIDATOR_HPP
