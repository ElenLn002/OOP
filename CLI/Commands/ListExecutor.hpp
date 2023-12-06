#ifndef LISTEXECUTOR_HPP
#define LISTEXECUTOR_HPP

#include "CommandExecutor.hpp"

class ListExecutor : public CommandExecutor {
public:
    void execute() override;
};

#endif // !LISTEXECUTOR_HPP
