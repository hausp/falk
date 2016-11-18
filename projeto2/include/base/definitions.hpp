
#ifndef FALK_DEFINITIONS_HPP
#define FALK_DEFINITIONS_HPP

#include <complex>

#include "evaluator/evaluator.hpp"
#include "operators.hpp"
#include "sma/value.hpp"
#include "types.hpp"

namespace falk {
    using analyser = ev::evaluator;
    
    using real = analyser::real;
    using complex = analyser::complex;
    using boolean = analyser::boolean;

    using value = value<analyser>;


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
