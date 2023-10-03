#include "CommandValidator.hpp"


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

    for (const auto& attr : attributes) 
        if (attr[0] == '-' && allowedAttributes.find(attr) == allowedAttributes.end()) {
            std::cout << shape << " cannot have attribute: " << attr << std::endl;
            return false;
        }
    }

    return true;
}