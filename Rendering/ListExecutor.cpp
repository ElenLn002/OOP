#include "ListExecutor.hpp"

ListExecutor::ListExecutor(const std::map<int, std::string>& itemsMap)
    : itemsMap(itemsMap) {}

void ListExecutor::execute(std::map<int, std::string>& itemsMap) {
    resultPrinter.printItems(itemsMap); 
