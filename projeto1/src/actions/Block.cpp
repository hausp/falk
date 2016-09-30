#include "Action.hpp"


void Block::add(Action* action) {
    if (action) {
        lines.push_back(action);
    }
}

std::string Block::to_string(unsigned indent) const {
    std::string out;
    size_t i = 0;
    for (auto& line : lines) {
        if (line) {
            out += line->to_string(indent);
            if (i < lines.size() - 1) {
                out += "\n";
            }
        }
        i++;
    }
    return out;
}
