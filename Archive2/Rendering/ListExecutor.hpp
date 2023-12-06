#ifndef LISTEXECUTOR_HPP
#define LISTEXECUTOR_HPP

#include "RenderingInterface.hpp"

#include <map>
#include <string>


class ListExecutor : public RenderingInterface {
public:
    ListExecutor(const std::map<int, std::string>& itemsMap);
    void execute(std::map<int, std::string>& itemsMap) override;

private:
    const std::map<int, std::string>& itemsMap;
};

#endif // !LISTEXECUTOR_HPP
