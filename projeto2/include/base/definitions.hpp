
#ifndef FALK_DEFINITIONS_HPP
#define FALK_DEFINITIONS_HPP

#include "evaluator/Evaluator.hpp"
#include "operators.hpp"
#include "types.hpp"

namespace falk {

    using Analyser = Evaluator;
    using real = Analyser::real;
    using complex = Analyser::complex;
    using boolean = Analyser::boolean;
}

#endif /* FALK_DEFINITIONS_HPP */
