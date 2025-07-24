#include "../include/engine.hpp"
#include "../include/game.hpp"

namespace Engine {
    void init() {
        // Set up environment, preload data
    }

    void run() {
        Game::showTitle();
        Game::startIntro();
        Game::playClues();
        Game::enterFinalPassword();
        // Game::gameOver(); // No longer needed, handled in enterFinalPassword
    }

    void shutdown() {
        // Clean up if needed
    }
}
