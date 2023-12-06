#ifndef REMOVEITEMFROMSLIDE_HPP
#define REMOVEITEMFROMSLIDE_HPP

#include "IAction.hpp"
#include "Document.hpp"

class RemoveItemFromSlide : public IAction {
    int itemID;
    size_t slideNumber;

public:
    RemoveItemFromSlide(int itemID, size_t slideNumber)
        : itemID(itemID), slideNumber(slideNumber) {}

    std::shared_ptr<IAction> execute(std::shared_ptr<Document>& document) override;
};

#endif //REMOVEITEMFROMSLIDE_HPP
