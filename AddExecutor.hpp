#ifndef ADDEXECUTOR_HPP
#define ADDEXECUTOR_HPP

#include <string>
#include <map>

class AddExecutor {
public:
    AddExecutor(const std::string& restOfTheLine);
    void addToMap(std::map<int, std::string>& itemsMap);

private:
    std::string addedItems;
};


#endif //ADDEXECUTOR_HPP