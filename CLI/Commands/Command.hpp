#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <map>
#include <string>

class Command {
public:
    virtual void execute() = 0;

protected:

    bool isItem(const std::string& type);
    bool isSlide(const std::string& type);

//this list is temporary
    std::map<int, std::string>& itemsMap;
    std::string addedAttributes;
    int ID;
    std::string newAttributes;
    int* initialItemID;
    std::string filePath;
    std::map<int, std::string>& itemsMap;
    int itemID;
    const std::string& type;
};

#endif // COMMAND_HPP
