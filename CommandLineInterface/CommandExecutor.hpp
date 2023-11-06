#ifndef COMMANDEXECUTOR_HPP
#define COMMANDEXECUTOR_HPP

#include <map>
#include <string>

class CommandExecutor {
public:
    virtual void execute(std::map<int, std::string>& itemsMap) = 0;
};

#endif // COMMANDEXECUTOR_HPP
