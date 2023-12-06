#ifndef IACTION_HPP
#define IACTION_HPP

#include <memory>
#include "Document.hpp"

class IAction {
public:
    virtual std::shared_ptr<IAction> execute(std::shared_ptr<Document>& document) = 0;
    virtual ~IAction() = default;
};

#endif // !IACTION_HPP
