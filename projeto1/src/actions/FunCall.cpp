#include "Action.hpp"

FunCall::FunCall(const std::string& name, Action* args_list)
 : name(name), args(dynamic_cast<ExpressionList*>(args_list)),
   fail(args->error()) { }

std::string FunCall::to_string(unsigned indent) const {
    std::string result;
    if (!error()) {
        result += name;
        result += "[" + std::to_string(args->size()) + " params]";
        for (auto& arg : *args) {
            result += " " + arg->to_string();
        }
    }
    return result;
}

Type FunCall::type() const {
    return symbols.typeof(name);
}
