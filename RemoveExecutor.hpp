#ifndef REMOVEEXECUTOR_HPP
#define REMOVEEXECUTOR_HPP

#include <string>
#include <map>

class RemoveExecutor : public CommandExecutor {
public:
    RemoveExecutor(int ID);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    int itemID;
};

#endif //REMOVEEXECUTOR_HPP
