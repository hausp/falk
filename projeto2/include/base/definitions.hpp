
#ifndef FALK_DEFINITIONS_HPP
#define FALK_DEFINITIONS_HPP

#include "ev/evaluator.hpp"
#include "types.hpp"

namespace falk {
    // Defines what kind of analyser will be used.
    // Usually, an evaluator or a translater.
    using analyser = ev::evaluator;
    
    // Propagates aliases from analyser to namespace falk.
    // This trick makes things easier to change.
    
    // Semantic types (objects) definitions.
    using real = analyser::real;
    using complex = analyser::complex;
    using boolean = analyser::boolean;
    using array = analyser::array;
    using matrix = analyser::matrix;
    using scalar = analyser::scalar;

    // Semantic abstractions definitions.
    using declaration = analyser::declaration;
    using empty = analyser::empty;
    using list = analyser::list;
    using lvalue = analyser::lvalue;
    using rvalue = analyser::rvalue;
}

#endif /* FALK_DEFINITIONS_HPP */
