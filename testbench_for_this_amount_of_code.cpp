int main() {
    // Create a CommandRegistry instance
    CommandRegistry commandRegistry;

    // Input a command
    std::cout << "Enter a command: ";
    std::string inputCommand;
    std::cin >> inputCommand;

    try {
        // Try to find the command
        CommandType commandType = commandRegistry.findCommand(inputCommand);
        std::cout << "Valid Command: " << commandType << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}