#ifndef CHANGEEXECUTOR_HPP
#define CHANGEEXECUTOR_HPP

#include <map>
#include<string>

class ChangeExecutor : public CommandExecutor {
public:
    ChangeExecutor(int ID, std::string& newAttributes);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    int itemID;
    std::string newAttributes;
};

#endif // CHANGEEXECUTOR_HPP
