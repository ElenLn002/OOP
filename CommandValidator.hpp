#ifndef COMMANDVALIDATOR_HPP
#define COMMANDVALIDATOR_HPP

#include <string>
#include <unordered_set>

class CommandValidator {
public:
    CommandValidator();
    bool validateShapeAttributes(const std::string& shape, const std::unordered_set<std::string>& attributes);

private:
    std::unordered_set<std::string> circleAttributes;
    std::unordered_set<std::string> rectangleAttributes;
    std::unordered_set<std::string> triangleAttributes;
};


#endif //COMMANDVALIDATOR_HPP