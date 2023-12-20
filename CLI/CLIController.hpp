#ifndef CLICONTROLLER_HPP
#define CLICONTROLLER_HPP

#include <memory>
#include <string>
#include <sstream>

#include "CommandHistory.hpp"


class CLIController{
public:
    CLIController(CommandFactory & factory) : factory_(factory) {}

    void executeCommands(std::istream & inputStream);

private:
    CommandFactory& factory_;
    CommandHistory history_;

    std::unique_ptr<Command> parseCommand(const std::string& input);
};
#endif //CLICONTROLLER_HPP
