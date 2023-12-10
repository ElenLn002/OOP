#include "LoadDocument.hpp"
#include "Includes.hpp"


void LoadDocument::execute(std::string& filename, std::shared_ptr<Document> doc) {
    std::ifstream inFile(filename); // Open the file for reading
    if (inFile.is_open()) {
        std::string line;
        std::shared_ptr<Slide> currentSlide;
        while (std::getline(inFile, line)) {
            if (line.find("Slide") != std::string::npos) {
                // Create a new slide and add it to the document
                currentSlide = std::make_shared<Slide>();
                doc->addSlide(currentSlide);
            }
            else if (line.find("Item ID") != std::string::npos && currentSlide) {
                // Parse item properties from the line
                std::istringstream iss(line);
                int id;
                std::string shape, attributes;
                Coordinate pos; // You'll need to define how to parse this
                iss >> id >> shape >> pos >> attributes; // Adjust this line based on your file format
                // Create a new item and add it to the current slide
                auto item = std::make_shared<Item>(id, shape, pos, attributes);
                currentSlide->addItem(item);
            }
            // Parse other lines as needed
        }
        inFile.close();
        std::cout << "Document loaded from " << filename << std::endl;
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}
