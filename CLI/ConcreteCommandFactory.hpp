#ifndef CONCRETECOMMANDFACTORY_HPP
#define CONCRETECOMMANDFACTORY_HPP

#include <CommandRegistry.hpp>
#include <CommandFactory.hpp>
#include <Command.hpp>

class ConcreteCommandFactory : public CommandFactory {
public:
    ConcreteCommandFactory(CommandRegistry& registry) : registry_(registry) {}

    std::unique_ptr<Command> createCommand(const std::string& commandType) override;
private:
    CommandRegistry& registry_;
}
endif //CONCRETECOMMANDFACTORY_HPP
