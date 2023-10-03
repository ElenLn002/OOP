#ifndef REMOVEEXECUTOR_HPP
#define REMOVEEXECUTOR_HPP

#include <string>
#include <map>

class RemoveExecutor {
public:
    RemoveExecutor(int index);
    void removeFromMap(std::map<int, std::string>& itemsMap);

private:
    int itemIndex;
};

#endif //REMOVEEXECUTOR_HPP