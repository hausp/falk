#include "Action.hpp"

FunCall::FunCall(const std::string& name, Action* args_list)
 : name(name), args(dynamic_cast<ExpressionList*>(args_list)),
   fail(args->error()) {

    if (!symbols.is_function(name)) {
        fail = true;
        utils::semantic_error<Error::UNDECLARED_VARIABLE>(name);
        return;
    }

    t = symbols.typeof(name);
    auto expected = symbols.params(name);
    auto num_expected = expected.size();
    auto num_actual = args->size();
    if (num_actual != num_expected) {
        fail = true;
        utils::semantic_error<Error::WRONG_PARAM_COUNT>(name, num_expected, num_actual);
        return;
    }

    auto it = expected.begin();
    for (auto& param : *args) {
        auto expected_type = it->type;
        auto actual_type = param->type();
        if (!utils::type_matches(expected_type, actual_type)) {
            fail = true;
            utils::semantic_error<Error::INCOMPATIBLE_PARAM>(it->name, expected_type, actual_type);
        }
        ++it;
    }
}

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
