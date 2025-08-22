#include "../include/game.hpp"
#include "../include/ascii.hpp"
#include "../include/clue.hpp"
#include "../include/terminalcolors.hpp"
#include "../include/fileutils.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

namespace Game {
    static std::vector<NotebookEntry> notebook;

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            std::cout << "\033[2J\033[1;1H";
        #endif
    }

    void addToNotebook(const std::string& clueName, const std::string& clueText, const std::string& solution) {
        notebook.push_back({clueName, clueText, solution});
    }

    void showNotebook() {
        Ascii::display("ascii/notebook.txt");
        std::cout << TermColor::MAGENTA << "\n--- NOTEBOOK ---\n" << TermColor::RESET;
        int idx = 1;
        for (const auto& entry : notebook) {
            std::cout << TermColor::YELLOW << idx << ". [" << entry.clueName << "]\n" << TermColor::RESET;
            std::cout << entry.clueText << "\n";
            std::cout << TermColor::CYAN << "Solution: " << entry.solution << "\n" << TermColor::RESET;
            std::cout << "----------------------\n";
            ++idx;
        }
        if (notebook.empty()) {
            std::cout << "(No clues found yet)\n";
        }
    }

    void showTitle() {
        clearScreen();
        Ascii::display("ascii/title.txt");
    }

    void startIntro() {
        Ascii::displayWithDelay("ascii/intro.txt", 80);
        std::cout << "\nPress Enter to begin trace...";
        std::cin.get();
        clearScreen();
    }

    void playClues() {
        auto& clues = Clue::getCluesMutable();
        for (auto& clue : clues) {
            bool solved = false;
            while (!solved) {
                clearScreen();
                Ascii::display(clue.file);
                std::cout << TermColor::CYAN << "[Enter your solution for this clue] (type 'notebook' to view clues): " << TermColor::RESET;
                std::string input;
                std::getline(std::cin, input);
                if (input == "notebook") {
                    showNotebook();
                    std::cout << TermColor::CYAN << "[Enter your solution for this clue]: " << TermColor::RESET;
                    std::getline(std::cin, input);
                }
                if (Clue::checkSolution(input, clue)) {
                    std::cout << TermColor::GREEN << "✓ Clue Solved!\n\n" << TermColor::RESET;
                    clue.solved = true;
                    solved = true;
                    // Read clue text for notebook
                    std::string clueText = FileUtils::readFile(clue.file);
                    addToNotebook(clue.name, clueText, clue.solution);
                } else {
                    std::cout << TermColor::RED << "✗ Incorrect. Try again.\n\n" << TermColor::RESET;
                }
            }
        }
    }

    void enterFinalPassword() {
        const auto& clues = Clue::getClues();
        // Check if all clues are solved
        bool allSolved = true;
        std::vector<std::string> solutions;
        for (const auto& clue : clues) {
            if (!clue.solved) {
                allSolved = false;
            }
            solutions.push_back(clue.solution);
        }
        
        // Jumble the solutions using a deterministic pattern
        // Pattern: rotate right by 1 position, then swap middle with last
        if (solutions.size() >= 3) {
            // Original: [133, 2131456, 1917]
            
            // Step 1: Rotate right by 1: [133, 2131456, 1917] -> [1917, 133, 2131456]
            std::rotate(solutions.rbegin(), solutions.rbegin() + 1, solutions.rend());
            
            // Step 2: Swap middle with last: [1917, 133, 2131456] -> [1917, 2131456, 133]
            std::swap(solutions[1], solutions[2]);
            
            // Final result: 19172131456133 (different from original 13321314561917)
        }
        
        // Concatenate the jumbled solutions
        std::string masterPassword;
        for (const auto& solution : solutions) {
            masterPassword += solution;
        }
        if (!allSolved) {
            std::cout << TermColor::RED << "\nYou must solve all clues before attempting the final password.\n" << TermColor::RESET;
            gameOver(false);
            return;
        }
        int tries = 0;
        const int maxTries = 3;
        while (tries < maxTries) {
            std::cout << TermColor::YELLOW << "All clues decrypted. Enter master password (type 'notebook' to view clues):\n" << TermColor::RESET;
            std::cout << TermColor::CYAN << "Hint: The order spins like a wheel, then dances with its neighbors\n" << TermColor::RESET;
            std::cout << TermColor::YELLOW << "> " << TermColor::RESET;
            std::string pw;
            std::getline(std::cin, pw);
            if (pw == "notebook") {
                showNotebook();
                continue;
            }
            if (pw == masterPassword) {
                std::cout << TermColor::GREEN << "\n[Access Granted]\n" << TermColor::RESET;
                gameOver(true);
                return;
            } else {
                ++tries;
                std::cout << TermColor::RED << "\n[Incorrect. The system denies you.]\n" << TermColor::RESET;
                if (tries < maxTries) {
                    std::cout << TermColor::YELLOW << (maxTries - tries) << " tries remaining.\n" << TermColor::RESET;
                }
            }
        }
        gameOver(false);
    }

    void gameOver(bool win) {
        if (win) {
            Ascii::display("ascii/gameover_alt.txt");
            std::cout << "\nPress Enter to return to Nexus...";
            std::cin.get();
        } else {
            Ascii::display("ascii/gameover.txt");
            std::cout << "\nPress Enter to exit...";
            std::cin.get();
        }
    }
}
