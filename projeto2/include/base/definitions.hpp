
#ifndef FALK_DEFINITIONS_HPP
#define FALK_DEFINITIONS_HPP

#include "evaluator/evaluator.hpp"
#include "operators.hpp"
#include "sma/value.hpp"
#include "types.hpp"

namespace falk {
    using analyser = ev::evaluator;
    
    // using program = analyser::program;
    // using command = analyser::command;
    // using control = analyser::control;
    // using declaration = analyser::declaration;
    // using assignment = analyser::assignment;
    using identifier = analyser::identifier;
    using array_index = analyser::array_index;
    using matrix_index = analyser::matrix_index;
    using expression = analyser::expression;
    using value = analyser::value;
    using init_list = analyser::init_list;
    using function = analyser::function;


    using generic = value;
}

#endif /* FALK_DEFINITIONS_HPP */
