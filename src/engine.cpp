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
        std::cin.get();
        Game::clearScreen();
        Game::startIntro();
        Game::clearScreen();
        Game::playClues();
        Game::enterFinalPassword();

    }

    void shutdown() {
        Game::clearScreen();
    }
}
