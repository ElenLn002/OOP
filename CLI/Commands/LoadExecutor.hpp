#ifndef LOADEXECUTOR_HPP
#define LOADEXECUTOR_HPP

#include "CommandExecutor.hpp"

class LoadExecutor : public CommandExecutor {
public:
    void execute() override;
};

#endif //LOADEXECUTOR_HPP
