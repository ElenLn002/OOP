#ifndef ADDEXECUTOR_HPP
#define ADDEXECUTOR_HPP

#include <map>
#include <string>

class AddExecutor : public CommandExecutor {
public:
    AddExecutor(std::string restOfLine);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    std::string addedAttributes;
};


#endif //ADDEXECUTOR_HPP
