#ifndef ADDITEMTOSLIDE_HPP
#define ADDITEMTOSLIDE_HPP

#include "Document.hpp"
#include "IAction.hpp"

class AddItemToSlide : public IAction {
    std::shared_ptr<Item> item;
    size_t slideNumber;

public:
    AddItemToSlide(const std::shared_ptr<Item>& item, size_t slideNumber)
        : item(item), slideNumber(slideNumber) {}

    std::shared_ptr<IAction> execute(std::shared_ptr<Document>& document) override;
};

#endif //ADDITEMTOSLIDE_HPP
