#include "../include/engine.hpp"
#include "../include/game.hpp"
#include <limits>

namespace Engine {
    void init() {
        // Set up environment, preload data
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
        // Game::gameOver(); // No longer needed, handled in enterFinalPassword
    }

    void shutdown() {
        // Clean up if needed
    }
}
