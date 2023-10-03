#include "RemoveExecutor.hpp"

SaveExecutor::SaveExecutor(const std::string& filePath, const std::map<int, std::string>& itemsMap)
    : filePath(filePath), itemsMap(itemsMap) {}

void SaveExecutor::execute() {
    std::ofstream outputFile(filePath);

    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file for saving." << std::endl;
        return;
    }

    // Write the content of the itemsMap to the file
    for (const auto& entry : itemsMap) {
        outputFile << entry.first << " " << entry.second << std::endl;
    }

    std::cout << "Content saved to file: " << filePath << std::endl;

    outputFile.close();
}
