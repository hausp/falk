#include "ActionStacker.hpp"
#include "Action.hpp"
#include "utils.hpp"

ActionStacker::~ActionStacker() {
    while (!actions.empty()) {
        popDelete();
    }
}

void ActionStacker::push(Action* action) {
    actions.push_back(action);
}

void ActionStacker::popDelete() {
    delete top();
    actions.pop_back();
}

Action* ActionStacker::pop() {
    auto t = top();
    actions.pop_back();
    return t;
}

Action* ActionStacker::top() {
    return actions.back();
}

void ActionStacker::print() const {
    for (auto& action : actions) {
        auto content = action->to_string();
        std::cout << content;
        if (!content.empty()) {
            std::cout << std::endl;
        }
    }
}
