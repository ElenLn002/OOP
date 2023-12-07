#ifndef SERIALIZINGINTERFACE_HPP
#define SERIALIZINGINTERFACE_HPP

#include <map>
#include <string>

class SerializingInterface {
    virtual void execute(std::map<int, std::string>& itemsMap) = 0;
};

#endif //SERIALIZINGINTERFACE_HPP
