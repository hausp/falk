#include "Action.hpp"


void Block::add(Action* action) {
	if (action) {
		lines.push_back(action);
	}
}

std::string Block::to_string(unsigned indent) const {
	auto spaces = std::string(indent, ' ');
	std::string out;
	for (auto& line : lines) {
		if (line) {
			out += spaces;
			out += line->to_string();
			out += "\n";
		}
	}
	return out;
}
