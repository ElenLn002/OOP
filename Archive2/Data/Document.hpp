#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <vector>

class Document {
public:
    Document()=default;

    void addSlide(const std::shared_ptr<Slide>& slide);
    const std::vector<std::shared_ptr<Slide>>& getSlides() const;

private:
    std::vector<std::shared_ptr<Slide>> slides;
};

#endif //DOCUMENT_HPP
