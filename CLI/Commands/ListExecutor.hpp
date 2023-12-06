#ifndef LISTEXECUTOR_HPP
#define LISTEXECUTOR_HPP

#include "RenderingInterface.hpp"

class ListExecutor : public CommandExecutor {
public:
    void execute() override;
};

#endif // !LISTEXECUTOR_HPP
