#ifndef DISPLAYEXECUTOR_HPP
#define DISPLAYEXECUTOR_HPP

#include <string>
#include <map>

class DisplayExecutor {
public:
    DisplayExecutor(const std::map<int, std::string>& itemsMap);
    void execute();

private:
    const std::map<int, std::string>& itemsMap;
};


#endif //DISPLAYEXECUTOR_HPP