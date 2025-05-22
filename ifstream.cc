#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("hello.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    if (file.fail() && !file.eof()) {
        std::cerr << "Error reading from file" << std::endl;
    }

    file.close();
    return 0;
}

