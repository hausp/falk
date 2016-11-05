
#include <cmath>
#include <complex>

#include "interpreter/base.hpp"
#include "definitions.hpp"

namespace {
    using complex = std::complex<double>;
}

// As Ghabriel wishes
template<>
double falk::pow<double>(const double& d1, const double& d2) {
    return std::pow(d1, d2);
}

template<>
complex falk::pow<complex>(const complex& c1, const complex& c2) {
    return std::pow(c1, c2);
}