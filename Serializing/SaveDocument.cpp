#include "SaveDocument.hpp"
#include "Includes.hpp"

void SaveDocument::execute(const std::string& filename, std::shared_ptr<Document> doc) {
    std::ofstream outFile(filename); 
    if (outFile.is_open()) {
        outFile << "Document Content:" << std::endl;
        for (size_t i = 1; i <= doc->getNumSlides(); ++i) {
            auto slide = doc->getSlide(i);
            outFile << "Slide " << i << ":\n";
            if (slide) {
                for (const auto& item : slide->itemsMap) {
                    outFile << "Item ID: " << item.first << ", Shape: " << item.second->getShape()
                        << ", Attributes: " << item.second->getAttributes() << "\n";
                }
            }
        }
        outFile.close();
        std::cout << "Document saved to " << filename << std::endl;
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}
