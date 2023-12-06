#ifndef RENDERINGINTERFACE_HPP
#define RENDERINGINTERFACE_HPP

#include <map>
#include <string>

class RenderingInterface {
public:
    virtual void execute(std::map<int, std::string>& itemsMap) = 0;
};

#endif //RENDERINGINTERFACE_HPP