
#ifndef FALK_DEFINITIONS_HPP
#define FALK_DEFINITIONS_HPP

#include "evaluator/evaluator.hpp"
#include "evaluator/evaluator.hpp"
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

    // Semantic abstractions definitions.
    using value = analyser::value;
}

#endif /* FALK_DEFINITIONS_HPP */
