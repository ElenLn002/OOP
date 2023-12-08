#ifndef CHANGEITEMTOSLIDE_HPP
#define CHANGEITEMTOSLIDE_HPP

#include <string>
#include <IAction>

class ChangeItemOfSlide : public IAction {
    int itemID;
    size_t slideNumber;
    std::string newAttributes;  // Add a member variable to hold the new attributes

public:
    ChangeItemOfSlide(int itemID, size_t slideNumber, const std::string& newAttributes)
        : itemID(itemID), slideNumber(slideNumber), newAttributes(newAttributes) {}

    std::shared_ptr<IAction> execute() override;
};
#endif //CHANGEITEMTOSLIDE_HPP
