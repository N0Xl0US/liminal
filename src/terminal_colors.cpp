#include "../include/terminal_colors.hpp"

namespace TermColor {
    std::string colorize(const std::string& text, const std::string& color) {
        return color + text + RESET;
    }
}
