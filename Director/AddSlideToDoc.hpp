#ifndef ADDSLIDETODOC_HPP
#define ADDSLIDETODOC_HPP

#include "IAction.hpp"
#include "Document.hpp"

class AddSlideToDoc : public IAction {
    std::shared_ptr<Slide> slide;
public:
    AddSlideToDoc(const std::shared_ptr<Slide>& slide);
    std::shared_ptr<IAction> execute(std::shared_ptr<Document>& document) override;
};

#endif //ADDSLIDETODOC_HPP
