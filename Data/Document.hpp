#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <vector>

class Document {
public:
    void addSlide(const std::shared_ptr<Slide>& slide);
    void removeSlide(int slideID);
    std::shared_ptr<Slide> getSlide(int slideID) const;

private:
    std::vector<std::shared_ptr<Slide>> slides;
};

#endif //DOCUMENT_HPP
