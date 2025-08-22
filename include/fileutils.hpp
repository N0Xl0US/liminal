#pragma once
#include <string>
#include <vector>

namespace FileUtils {
    std::string readFile(const std::string& path);
    std::vector<std::string> readLines(const std::string& path);
}
