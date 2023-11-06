#ifndef LISTEXECUTOR_HPP
#define LISTEXECUTOR_HPP

#include "CommandExecutor.hpp"

#include <map>
#include <string>


class ListExecutor : public CommandExecutor {
public:
    ListExecutor(const std::map<int, std::string>& itemsMap);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    const std::map<int, std::string>& itemsMap;
};

#endif // !LISTEXECUTOR_HPP
