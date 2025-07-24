#pragma once
#include <string>
#include <vector>

namespace Game {
    struct NotebookEntry {
        std::string clueName;
        std::string clueText;
        std::string solution;
    };
    void showTitle();
    void startIntro();
    void playClues();
    void enterFinalPassword();
    void gameOver(bool win);
    void addToNotebook(const std::string& clueName, const std::string& clueText, const std::string& solution);
    void showNotebook();
    void clearScreen();
}
