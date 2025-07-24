#include "include/engine.hpp"
#include "include/clue.hpp"

int main() {
    Engine::init();
    Clue::loadClues();
    Engine::run();
    Engine::shutdown();
    return 0;
}
