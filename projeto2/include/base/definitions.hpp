
#ifndef FALK_DEFINITIONS_HPP
#define FALK_DEFINITIONS_HPP

#include "ev/evaluator.hpp"
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

    // Semantic abstractions definitions.
    using value = analyser::value;
    using list = analyser::list;
}

#endif /* FALK_DEFINITIONS_HPP */
