#ifndef CHANGEEXECUTOR_HPP
#define CHANGEEXECUTOR_HPP

#include <map>
#include<string>

class ChangeExecutor {
public:
    ChangeExecutor(int index, const std::string& newArguments);
    void execute(std::map<int, std::string>& itemsMap);

private:
    int itemIndex;
    std::string newArguments;
};

#endif // CHANGEEXECUTOR_HPP
