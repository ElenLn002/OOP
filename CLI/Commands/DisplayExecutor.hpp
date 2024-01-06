#ifndef DISPLAYEXECUTOR_HPP
#define DISPLAYEXECUTOR_HPP

#include "Command.hpp"

class Display : public Command {
public:
    void execute() override;
};

#endif //DISPLAYEXECUTOR_HPP
