#include <any>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <variant>
#include <utility>
#include <unordered_map>
#include <string>



using Position = std::pair<double, double>;
using ID = int;
using Type = std::string;
using Key = std::string;
using Value = double;
using CommandType = std::string;
using AttributeList = std::vector<std::string>;
using Attributes = std::pair<Key, Value>;



class InputTaker {
public:

};


class Tokenizer {
private:
    std::string input;

public:
    std::istream& takeInput(std::istream& stream) {
        // Read input from the stream
        std::stringstream buffer;
        buffer << stream.rdbuf();
        input = buffer.str();
        return stream;
    }

    std::vector<std::string> getTokens() {
        std::vector<std::string> tokens;
        std::stringstream ss(input);
        std::string token;

        // Tokenize based on whitespace
        while (ss >> token) {
            tokens.push_back(token);
        }

        return tokens;
    }
};

class CommandRegistry {
public:
    CommandRegistry();
    CommandType findCommand(const std::string& commandName); // commandName is from getTokens

private:
    std::vector<CommandType> ValidCommands;
};

CommandRegistry::CommandRegistry() :
    ValidCommands{ "Add", "Remove", "Quit", "Display" } {}

CommandType CommandRegistry::findCommand(const std::string& commandName) {
    for (const auto& cmd : ValidCommands) {
        if (commandName == cmd) {
            return cmd;
        }
    }

    throw std::runtime_error("Invalid command.");
}

class Parser {
public:
    std::any commandParsing(std::istream&);
};

std::any commandParsing(std::istream& input) {
    /// TODO: this function will check if the 1st token is in the CommandRegistry(is a valid command)
    //if yes,it will add the rest of the command in a conttainer
    //if no, it will print an error message
}

struct CommandLine {
    int Id;
    std::string name;
    std::map<std::string, std::string> arguments;
};


class Executor {
public:
    virtual void CommandExecute(CommandType cmd) = 0;

protected:
    CommandType cmd;
    std::unordered_map<ID, AttributeList> CommandContainer;
    int Id = 0;
};

class AddExecutor : public Executor {
public:
    void CommandExecute(CommandType cmd);
};

void AddExecutor::CommandExecute(CommandType cmd) {
    {
        //    // Iterate through tokens and add to CommandContainer if they don't start with '-'
        //    for (size_t i = 2; i < tokens.size(); ++i) {
        //        const std::string& token = tokens[i];

        //        if (token[0] != '-') {
        //            // Token does not start with '-', add it to CommandContainer
        //            AttributeList.push_back(token);
        //        }
        //    }

        //}
    }

}




//class Item {
//private:
//    Position position;
//    ID id;
//    Type type;
//    ;
//
//public:
//    void setPos(Position);
//    Position getPos() const;
//    ID getID () const;
//    Type getType() const;
//    Value getAttribute(Key) const;
//    bool setAttribute(Key, Value);
//};
//
//void Item::setPos(Position pos) {
//    position = pos;
//}
//
//Position Item::getPos() const {
//    return position;
//}
//
//ID Item::getID() const {
//    return id;
//}
//
//Type Item::getType() const {
//    return type;
//}
//
//Value Item::getAttribute(Key key) const {
//    auto it = attributes.find(key);
//    if (it != attributes.end()) {
//        return it->second;
//    }
//    return 0.0;  // Return 0.0 if key not found
//}
//
//bool Item::setAttribute(Key key, Value value) {
//    // Allow updating existing attributes or adding new ones
//    attributes[key] = value;
//    return true;
//}
