#ifndef DISPLAYEXECUTOR_HPP
#define DISPLAYEXECUTOR_HPP

#include "CommandExxecutor.hpp"

class DisplayExecutor : public CommandExecutor {
public:
    void execute() override;
};

#endif //DISPLAYEXECUTOR_HPP
