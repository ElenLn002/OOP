#include "RemoveSlideFromDoc.cpp"
#include "Includes.hpp"

std::shared_ptr<IAction> RemoveSlideFromDoc:: execute()  {
    std::shared_ptr<Document> document = Application::getDocument();
    document->removeSlide(slideNumber);
    std::cout << "Slide with ID " << slideNumber << " removed from document." << std::endl;

    return AddSlideToDoc;
}
