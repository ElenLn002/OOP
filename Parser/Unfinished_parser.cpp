#include <iostream>
#include <map> //std::map
#include <vector>
#include <string>
#include <sstream> //std::stringstream
#include <utility> //std::pair

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
}; //Command











using Command = std::pair<std::string, std::vector<std::string>>;

class Parser {
public:
    Command ParsingInput(std::stringstream& inputStream) {
        std::stringstream operands;
        std::string token;
        std::string command_line;

        inputStream >> command_line;
        if (!inputStream) {
            throw std::runtime_error("Empty command line!")
        }

        if (token == "-op1") {
            inputStream >> token;
            operands << token << " ";
            inputStream >> token;
            if (token != "-op2") {
                throw std::runtime_error("Invalid command structure!")
            }
        }
        else if (token == "-op") {
            inputStream >> token;
            operands << token << " ";
        }
        else if (token == "-ops") {
            while (inputStream >> token) {
                operands << token << " ";
            }
        }
        else {
            throw std::runtime_error("Invalid command structure!")
        }

        return std::make_pair(command_line, operands);

    }// ParsingCommand

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



class CalculateResult {

};



class PrintResult {
public:
    void printRes(std::string);
};

void PrintResult::printRes(std::string result) {
    std::cout << "Result is: " << result << std::endl;
}