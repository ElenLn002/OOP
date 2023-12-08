#include "Includes.hpp"
#include "ChangeSlideID.cpp"

std::shared_ptr<IAction> ChangeSlideID::execute() {
    
    std::shared_ptr<Document> document = Application::getDocument();

    if (newSlideID <= document->getNumSlides() && newSlideID > 0 && newSlideID != slideNumber) {

        std::shared_ptr<Slide> slideToChange = document->getSlide(slideNumber);
        if (slideToChange) {
            document->removeSlide(slideNumber); // Remove the existing slide
            // Create a new slide with the new ID
            std::shared_ptr<Slide> newSlide = std::make_shared<Slide>();
            document->addSlide(newSlide);
            std::cout << "Slide ID changed from " << slideNumber << " to " << newSlideID << std::endl;
        }
        else {
            std::cout << "Slide with ID " << slideNumber << " not found." << std::endl;
        }
    }
    else {
        std::cout << "Invalid or duplicate new slide ID." << std::endl;
    }

    //return should be changed
    return nullptr;
}
