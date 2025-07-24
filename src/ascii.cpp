#include "../include/ascii.hpp"
#include "../include/fileutils.hpp"
#include <iostream>
#include <thread>
#include <chrono>

namespace Ascii {
    void display(const std::string& filename) {
        std::string content = FileUtils::readFile(filename);
        std::cout << content << std::endl;
    }

    void displayWithDelay(const std::string& filename, int ms) {
        std::vector<std::string> lines = FileUtils::readLines(filename);
        for (const std::string& line : lines) {
            std::cout << line << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        }
    }
}
