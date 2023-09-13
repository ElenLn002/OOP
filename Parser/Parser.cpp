#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

class InputHandler { // this class just gets the input
public:
    std::stringstream getInput();

private:
    std::string ssInput;
};//InputHandler


std::stringstream InputHandler::getInput() {

    getline(std::cin, ssInput);

    return std::stringstream(ssInput);
}


enum class Commands {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    CMP
};

struct ParseResult {
    /* ParseResult(const std::string& cmd, const std::stringstream& argsStream) :
         command(cmd),
         arguments(argsStream.str()) // Convert the stringstream to a string
     {}*/

    std::string command;
    std::vector<std::string> arguments;
};

class Parser {
public:
    ParseResult parseCommand(std::stringstream& inputStream) {
        std::string command;
        std::string arguments;

        inputStream >> command;
        if (!inputStream) {
            throw std::runtime_error("Invalid command format.");
        }

        std::string token;
        while (inputStream >> token) {
            if (token == "-args") {
                while (inputStream >> token) {
                    arguments += token + " ";
                }
            }
            else if (token == "-arg1") {
                if (!(inputStream >> token)) {
                    throw std::runtime_error("Invalid command format.");
                }
                arguments += token + " ";

                if (!(inputStream >> token) || token != "-arg2" || !(inputStream >> token)) {
                    throw std::runtime_error("Invalid command format.");
                }
                arguments += token + " ";
            }
            else if (token == "-arg") {
                if (!(inputStream >> token)) {
                    throw std::runtime_error("Invalid command format.");
                }
                arguments += token + " ";
            }
            else {
                throw std::runtime_error("Invalid command format.");
            }
        }

        // return ParseResult(command, arguments);
    }

private:
    std::map<std::string, Commands> commandMap = {
        {"ADD", Commands::ADD},
        {"SUB", Commands::SUB},
        {"MUL", Commands::MUL},
        {"DIV", Commands::DIV},
        {"MOD", Commands::MOD},
        {"CMP", Commands::CMP}
    };
};

class PrintResult {
public:
    void printRes(std::string);
};

void PrintResult::printRes(std::string result) {
    std::cout << "Result is: " << result << std::endl;
}

//unfinished,still lots of things to add and/or change