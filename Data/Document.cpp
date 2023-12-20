#include "Document.hpp"

void Document::addSlide(const std::shared_ptr<Slide>& slide) {
    slides.push_back(slide);
}


void Document::removeSlide(int slideID) {
    if (slideID > 0 && slideID <= slides.size()) {
        slides.erase(slides.begin() + slideID - 1);
        std::cout << "Slide with ID " << slideID << " removed successfully." << std::endl;
    }
    else {
        std::cerr << "Invalid slide ID: " << slideID << std::endl;
    }
}


std::shared_ptr<Slide> Document::getSlide(int slideID) const {
    if (slideID > 0 && slideID <= slides.size()) {
        return slides[slideID - 1];
    }
    return nullptr;
}
