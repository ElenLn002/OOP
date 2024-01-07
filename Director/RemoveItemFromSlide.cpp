#include "RemoveITemFromSlide.hpp"
#include "Slide.hpp"

std::shared_ptr<IAction> RemoveItemFromSlide:: execute(std::shared_ptr<Document>& document)  {
    std::shared_ptr<Slide> slide = document->getSlide(slideNumber);

    if (slide) {
        slide->removeItem(itemID); // Assuming removeItem method in Slide takes itemID
        std::cout << "Item with ID " << itemID << " removed from slide " << slideNumber << std::endl;
    }
    else {
        std::cout << "Slide " << slideNumber << " does not exist." << std::endl;
    }

   
    return AddItemToSlide; // It should return AddItemToSlide
}
