#ifndef CLICONTROLLER_HPP
#define CLICONTROLLER_HPP

#include <string>
#include <sstream>

#include "CommandHistory.hpp"
#include "CommandRegistry.hpp"


class CLIController {
public:
    void executeCommands(std::istream& inputStream);

private:
    CommandRegistry registry_;
    CommandHistory history_;

    std::unique_ptr<Command> run(const std::string& input);
};
#endif //CLICONTROLLER_HPP
