#ifndef CHANGESLIDEID_HPP
#define CHANGESLIDEID_HPP

#include <memory>

class ChangeSlideID : public IAction {
    size_t slideNumber;
    size_t newSlideID;

public:
    ChangeSlideID(size_t slideNumber, size_t newSlideID)
        : slideNumber(slideNumber), newSlideID(newSlideID) {}

    std::shared_ptr<IAction> execute() override;
};

#endif  //CHANGESLIDEID_HPP
