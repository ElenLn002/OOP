#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <stdexcept>
#include <unordered_set>
#include <map>

#include "CommandRegistry.hpp"
#include "CommandValidator.hpp"
#include "ShapeRegistry.hpp"
#include "Parser.hpp"


class Controller {
public:
    void run();
};

#endif //CONTROLLER_HPP