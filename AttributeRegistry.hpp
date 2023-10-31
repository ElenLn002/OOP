#ifndef ATTRIBUTEREGISTRY_HPP
#define ATTRIBUTEREGISTRY_HPP

#include <vector>
#include <string>

class AttributeRegistry {
public:
    AttributeRegistry();
    bool areValidAttributes(const std::vector<std::string>& attr);

private:
    std::vector<std::string> validAttributes;
};

#endif // ATTRIBUTEREGISTRY_HPP
