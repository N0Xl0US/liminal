#include "../include/clue.hpp"
#include <algorithm>
#include <cctype>

namespace Clue {
    static std::vector<ClueData> clues;

    void loadClues() {
        clues = {
            { "Tokyo", "ascii/clues/clue_tokyo.txt", "133", "Look at the time gaps." },
            { "Luanda", "ascii/clues/clue_africa.txt", "2131456", "Poetry encodes the sequence." },
            { "Sydney", "ascii/clues/clue_sydney.txt", "1917", "Frequency is the code." }
        };
    }

    bool checkSolution(const std::string& input, const ClueData& clue) {
        auto trim = [](const std::string& s) -> std::string {
            size_t start = s.find_first_not_of(" \t\n\r");
            size_t end = s.find_last_not_of(" \t\n\r");
            if (start == std::string::npos || end == std::string::npos) return "";
            return s.substr(start, end - start + 1);
        };
        auto toLower = [](const std::string& s) -> std::string {
            std::string out = s;
            std::transform(out.begin(), out.end(), out.begin(), [](unsigned char c){ return std::tolower(c); });
            return out;
        };
        std::string user = toLower(trim(input));
        std::string sol = toLower(trim(clue.solution));
        return user == sol;
    }

    const std::vector<ClueData>& getClues() {
        return clues;
    }

    std::vector<ClueData>& getCluesMutable() {
        return clues;
    }
}
