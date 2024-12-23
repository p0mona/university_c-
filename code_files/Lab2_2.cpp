//Task 2

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstring>

void copyFileWithVector(const std::string& source, const std::string& destination, std::size_t bufferSize = 256) {
    std::ifstream inputFile(source, std::ios::binary);
    std::ofstream outputFile(destination, std::ios::binary);

    if (!inputFile) {
        throw std::runtime_error("Could not open source file: " + source);
    }
    if (!outputFile) {
        throw std::runtime_error("Could not open destination file: " + destination);
    }

    std::vector<char> buffer(bufferSize);
    while (inputFile.read(buffer.data(), buffer.size()) || inputFile.gcount() > 0) {
        outputFile.write(buffer.data(), inputFile.gcount());
    }
}

void copyFileWithUniquePtr(const std::string& source, const std::string& destination, std::size_t bufferSize = 256) {
    std::ifstream inputFile(source, std::ios::binary);
    std::ofstream outputFile(destination, std::ios::binary);

    if (!inputFile) {
        throw std::runtime_error("Could not open source file: " + source);
    }
    if (!outputFile) {
        throw std::runtime_error("Could not open destination file: " + destination);
    }

    std::unique_ptr<char[]> buffer(new char[bufferSize]);
    while (inputFile.read(buffer.get(), bufferSize) || inputFile.gcount() > 0) {
        outputFile.write(buffer.get(), inputFile.gcount());
    }
}

int main() {
    try {
        const std::string sourceFile = "/Users/polinabezukladnova/Documents/JPro/JPro/test.txt";
        const std::string destinationFileVector = "destination_vector.txt";
        copyFileWithVector(sourceFile, destinationFileVector);
        std::cout << "File copied using std::vector.\n";

        const std::string destinationFileUniquePtr = "destination_unique_ptr.txt";
        copyFileWithUniquePtr(sourceFile, destinationFileUniquePtr);
        std::cout << "File copied using std::unique_ptr.\n";
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}

