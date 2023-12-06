#include "AddItemToSlide.hpp"
#include "Slide.hpp"

std::shared_ptr<IAction> AddItemToSlide:: execute(std::shared_ptr<Document>& document) {
    std::shared_ptr<Slide> slide = document->getSlide(slideNumber);

    if (slide) {
        slide->addItem(item);
        std::cout << "Item added to slide " << slideNumber << std::endl;
    }
    else {
        std::cout << "Slide " << slideNumber << " does not exist." << std::endl;
    }

    // Return null for now 
    return nullptr; //I know that it should return remove
}
