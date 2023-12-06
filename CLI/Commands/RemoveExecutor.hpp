#ifndef REMOVEEXECUTOR_HPP
#define REMOVEEXECUTOR_HPP

#include "CommandExecutor.hpp"

class RemoveExecutor : public CommandExecutor {
public:
    void execute() override;
};

#endif //REMOVEEXECUTOR_HPP
