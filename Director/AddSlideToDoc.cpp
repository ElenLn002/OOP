#include "AddSlideToDoc.hpp"

#include "Slide.hpp"

AddSlideToDoc::AddSlideToDoc(const std::shared_ptr<Slide>& slide) : slide(slide) {}

std::shared_ptr<IAction> AddSlideToDoc::execute(std::shared_ptr<Document>& document) {
    if (document) {
        document->addSlide(slide);
        std::cout<<"Slide added to document!\n"; // You may need to define UndoAddSlide class for undo functionality
    }
    else {
        // will be changed
        return nullptr;
    }
}
