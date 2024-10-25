#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

#include <string>
#incl
class CommandFactory {
public:
    virtual std::unique_ptr<Command> createCommand(const std::string& commandType) = 0;
    virtual ~CommandFactory() = default;
};

#endif //COMMANDFACTORY_HPP
