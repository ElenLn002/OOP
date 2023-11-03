#include "ShapeRegistry.hpp"

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
