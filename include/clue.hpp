#pragma once
#include <string>
#include <vector>

namespace Clue {
    struct ClueData {
        std::string name;
        std::string file;
        std::string solution;
        std::string hint;
        bool solved = false;
    };

    void loadClues();
    bool checkSolution(const std::string& input, const ClueData& clue);
    const std::vector<ClueData>& getClues();
    std::vector<ClueData>& getCluesMutable();
}
