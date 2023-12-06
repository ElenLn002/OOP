#ifndef UNDO_HPP
#define UNDO_HPP

#include "CommandExecutor.hpp"


class Undo : public CommandExecutor {
public:
    void execute() override;
};

#endif // UNDO_HPP
