#ifndef REMOVESLIDEFROMDOC_HPP
#define REMOVESLIDEFROMDOC_HPP

#include "IAction"

class RemoveSlideFromDoc : public IAction {
    size_t slideNumber;

public:
    RemoveSlideFromDoc(size_t slideNumber) : slideNumber(slideNumber) {}

    std::shared_ptr<IAction> execute() override;
};


#endif //REMOVESLIDEFROMDOC_HPP
