#include "Action.hpp"

Fun::Fun(Type type, const std::string& name)
 : name(name), ret(type) {
}

void Fun::inject(Action* params) {
    auto param_list = dynamic_cast<ParamList*>(params);
    for (auto& pair : *param_list) {
        symbols.declare(pair.first, pair.second);
    }
}

void Fun::bind(Action* args, Action* content) {
    params = args;
    fail = fail || params->error();

    auto param_list = dynamic_cast<ParamList*>(args);
    if (content == nullptr) {
        fail = fail || !symbols.declare_function(ret, name, param_list);
    } else {
        fail = fail || !symbols.define_function(ret, name, param_list, content);
    }

    if (!fail) {
        body = content;
    }
}

std::string Fun::to_string(unsigned indent) const {
    std::string result;
    if (!error() && body != nullptr) {
        result += std::string(indent, ' ');
        result += utils::to_string(type()) + " fun: " + name;
        result += " (params: ";
        result += params->to_string();
        result += ")\n";
        result += body->to_string(indent + 2);
    }
    return result;
}
