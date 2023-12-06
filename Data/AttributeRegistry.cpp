#include "AttributeRegistry.hpp"

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
