
#ifndef FALK_EVALUATOR_ARITHMETIC_EXPR_HPP
#define FALK_EVALUATOR_ARITHMETIC_EXPR_HPP

#include "base/operators.hpp"
#include "Evaluator.hpp"
#include "rvalue.hpp"

namespace falk {
    class Evaluator::arithmetic_expr : public ast::tdnode<2, Evaluator> {
        friend class Evaluator;
     public:
        
     private:
        op::Arithmetical operation;
    };
}

#endif /* FALK_EVALUATOR_ARITHMETIC_EXPR_HPP */
