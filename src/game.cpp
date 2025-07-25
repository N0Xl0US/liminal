#include "../include/game.hpp"
#include "../include/ascii.hpp"
#include "../include/clue.hpp"
#include "../include/terminal_colors.hpp"
#include "../include/file_utils.hpp"

#include <iostream>
#include <vector>
#include <algorithm>

namespace Game {
    static std::vector<NotebookEntry> notebook;

    void clearScreen() {
        // ANSI escape code to clear screen
        std::cout << "\033[2J\033[1;1H";
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
        Ascii::displayWithDelay("ascii/intro.txt", 80); // Will slow further in next step
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
        std::string masterPassword;
        for (const auto& clue : clues) {
            if (!clue.solved) {
                allSolved = false;
            }
            masterPassword += clue.solution;
        }
        if (!allSolved) {
            std::cout << TermColor::RED << "\nYou must solve all clues before attempting the final password.\n" << TermColor::RESET;
            gameOver(false);
            return;
        }
        int tries = 0;
        const int maxTries = 3;
        while (tries < maxTries) {
            std::cout << TermColor::YELLOW << "All clues decrypted. Enter master password (type 'notebook' to view clues):\n> " << TermColor::RESET;
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
        } else {
            Ascii::display("ascii/gameover.txt");
        }
    }
}
