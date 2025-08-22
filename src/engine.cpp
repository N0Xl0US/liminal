#include "../include/engine.hpp"
#include "../include/game.hpp"
#include <iostream>
#include <limits>

namespace Engine {
    void init() {
    }

    void run() {
        Game::showTitle();
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        Game::clearScreen();
        Game::startIntro();
        Game::clearScreen();
        Game::playClues();
        Game::enterFinalPassword();

    }

    void shutdown() {
        // Clean up if needed
        Game::clearScreen();
    }
}
