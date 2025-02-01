#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

void displayMenu() {
    std::cout << "\nWelcome to Simple C++ IDE\n";
    std::cout << "1. Create New File\n";
    std::cout << "2. Edit Existing File\n";
    std::cout << "3. Compile and Run Code\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose an option: ";
}

void createNewFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error creating file: " << filename << std::endl;
        return;
    }
    std::cout << "File created successfully. You can start editing it.\n";
    outFile.close();
}

void editFile(const std::string& filename) {
    std::string line;
    std::ofstream outFile(filename, std::ios::app);
    if (!outFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::cout << "Editing " << filename << ". Type 'exit' on a new line to stop editing.\n";

    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, line);
        if (line == "exit") {
            break;
        }
        outFile << line << "\n";
    }
    outFile.close();
    std::cout << "Changes saved.\n";
}

void compileAndRun(const std::string& filename) {
    std::string command = "g++ " + filename + " -o output && ./output";
    std::cout << "Compiling and Running...\n";
    int result = system(command.c_str());
    if (result == 0) {
        std::cout << "Execution completed successfully.\n";
    } else {
        std::cerr << "Error during compilation or execution.\n";
    }
}

int main() {
    std::string filename;
    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();  // To clear the newline character left in the buffer

        switch (choice) {
            case 1:
                std::cout << "Enter the filename to create: ";
                std::getline(std::cin, filename);
                createNewFile(filename);
                break;
            case 2:
                std::cout << "Enter the filename to edit: ";
                std::getline(std::cin, filename);
                if (!fs::exists(filename)) {
                    std::cerr << "File does not exist.\n";
                    break;
                }
                editFile(filename);
                break;
            case 3:
                std::cout << "Enter the filename to compile and run: ";
                std::getline(std::cin, filename);
                if (!fs::exists(filename)) {
                    std::cerr << "File does not exist.\n";
                    break;
                }
                compileAndRun(filename);
                break;
            case 4:
                std::cout << "Exiting IDE...\n";
                running = false;
                break;
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
