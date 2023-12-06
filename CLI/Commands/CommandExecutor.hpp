#ifndef COMMANDEXECUTOR_HPP
#define COMMANDEXECUTOR_HPP

#include <map>
#include <string>

class CommandExecutor {
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

#endif // COMMANDEXECUTOR_HPP
