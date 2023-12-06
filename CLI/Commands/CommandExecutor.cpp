#include "CommandExecutor.hpp"

bool CommandExecutor::isItem(const std::string& type) {
    return type == "item";
}

bool CommandExecutor::isSlide(const std::string& type) {
    return type == "slide";
}
