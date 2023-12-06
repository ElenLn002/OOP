#ifndef LOADEXECUTOR_HPP
#define LOADEXECUTOR_HPP

#include "SerializingInterface.hpp"

class LoadExecutor : public SerializingInterface {
public:
    LoadExecutor(const std::string& filePath, int* initialItemID);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    std::string filePath;
    int* initialItemID;
};

#endif //LOADEXECUTOR_HPP
