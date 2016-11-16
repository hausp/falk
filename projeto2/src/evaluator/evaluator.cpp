
#include "evaluator/evaluator.hpp"
#include "evaluator/expr.hpp"

falk::ev::evaluator::value falk::ev::evaluator::pow(const value& lhs,
                                                    const value& rhs) {
    auto type = falk::resolve_types(lhs.type, rhs.type);
    if (type == Type::REAL) {
        // TODO
    } else {
        // TODO
    }
    return value{};
}