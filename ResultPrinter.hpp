#ifndef RESULTPRINTER_HPP
#define RESULTPRINTER_HPP

#include <map>
#include <string>


class ResultPrinter {
public:
    void printItem(int itemID, const std::string& itemAttributes);
    void printItems(const std::map<int, std::string>& itemsMap);
};

ResultPrinter resultPrinter;  

#endif // RESULTPRINTER_HPP
