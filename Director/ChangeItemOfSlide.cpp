#include "ChangeItemToSlide.hpp"
#include "Headers.hpp"

std::shared_ptr<IAction> ChangeItemOfSlide::execute() {
    std::shared_ptr<Document> document = Application::getDocument();
    std::shared_ptr<Slide> slide = document->getSlide(slideNumber);
    if (!slide) {
        std::cerr << "Error: Slide with ID " << slideNumber << " does not exist." << std::endl;
        return nullptr;
    }

    std::shared_ptr<Item> item = slide->getItem(itemID);
    if (item) {
        // Change the attributes of the item directly
        item->setAttributes(newAttributes);
        std::cout << "Item with ID " << itemID << " on slide " << slideNumber << " changed." << std::endl;
    }
    else {
        std::cout << "Item with ID " << itemID << " not found in slide " << slideNumber << "." << std::endl;
    }

    // Return nullptr as no further action is needed
    return nullptr;
}
