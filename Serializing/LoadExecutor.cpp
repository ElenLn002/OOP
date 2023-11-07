#include "LoadExecutor.hpp"

LoadExecutor::LoadExecutor(const std::string& filePath, int* initialItemID) : filePath(filePath), initialItemID(initialItemID) {}

void LoadExecutor::execute(std::map<int, std::string>& itemsMap) {
    std::ifstream inputFile(filePath);

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the specified file for loading." << std::endl;
        return;
    }

    std::string line;
    int nextID = 0;

    while (std::getline(inputFile, line)) {
        std::istringstream lineStream(line);
        int itemID;
        lineStream >> itemID;

        if (lineStream) {
            *initialItemID = std::max(*initialItemID, itemID + 1); 
            std::string attributes;
            std::getline(lineStream, attributes);
            itemsMap[itemID] = attributes;
        }
    }

    inputFile.close();

    std::cout << "Commands loaded from file: " << filePath << std::endl;
}
