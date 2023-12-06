#ifndef SAVEEXECUTOR_HPP
#define SAMOVEEXECUTOR_HPP

#include <string>
#include <map>

#include "SerializingInterface.hpp"

class SaveExecutor : public SerializingInterface {
public:
    SaveExecutor(std::string filePath, std::map<int, std::string>& itemsMap);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    std::string filePath;
    std::map<int, std::string>& itemsMap;
};

#endif //SAMOVEEXECUTOR_HPP
