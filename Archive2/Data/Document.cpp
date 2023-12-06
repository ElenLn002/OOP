#include "Document.hpp"

void Document::addSlide(const std::shared_ptr<Slide>& slide) {
    slides.push_back(slide);
}

const std::vector<std::shared_ptr<Slide>>& Document::getSlides() const {
    return slides;
}
