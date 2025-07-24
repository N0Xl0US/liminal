#include "../include/game.hpp"
#include "../include/ascii.hpp"
#include "../include/clue.hpp"
#include "../include/terminal_colors.hpp"

#include <iostream>

namespace Game {
    void showTitle() {
        Ascii::display("ascii/title.txt");
    }

    void startIntro() {
        Ascii::displayWithDelay("ascii/intro.txt", 50);
    }

    void playClues() {
        auto& clues = Clue::getCluesMutable();
        for (auto& clue : clues) {
            bool solved = false;
            while (!solved) {
                Ascii::display(clue.file);
                std::cout << TermColor::CYAN << "[Enter your solution for this clue]: " << TermColor::RESET;
                std::string input;
                std::getline(std::cin, input);

                if (Clue::checkSolution(input, clue)) {
                    std::cout << TermColor::GREEN << "✓ Clue Solved!\n\n" << TermColor::RESET;
                    clue.solved = true;
                    solved = true;
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
        std::cout << TermColor::YELLOW << "All clues decrypted. Enter master password:\n> " << TermColor::RESET;
        std::string pw;
        std::getline(std::cin, pw);

        if (pw == masterPassword) {
            std::cout << TermColor::GREEN << "\n[Access Granted]\n" << TermColor::RESET;
            gameOver(true);
        } else {
            std::cout << TermColor::RED << "\n[Incorrect. The system denies you.]\n" << TermColor::RESET;
            gameOver(false);
        }
    }

    void gameOver(bool win) {
        if (win) {
            Ascii::display("ascii/gameover_alt.txt");
        } else {
            Ascii::display("ascii/gameover.txt");
        }
    }
}
