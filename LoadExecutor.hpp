#ifndef LOADEXECUTOR_HPP
#define LOADEXECUTOR_HPP

#include <map>
#include <string>


class LoadExecutor {
public:
    LoadExecutor(std::map<int, std::string>& itemsMap);
    void execute();

private:
    std::map<int, std::string>& itemsMap;
};

#endif // !LOADEXECUTOR_HPP